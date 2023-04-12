/*
 *  Copyright (c) 2015, United States government as represented by the
 *  administrator of the National Aeronautics Space Administration.
 *  All rights reserved. This software was created at NASA Glenn
 *  Research Center pursuant to government contracts.
 */

/**
 * \file
 *
 * Generic abstraction API for on-board devices.  This is the implementation
 * of functions declared in iodriver_base.h
 */

#include "cfe_psp_module.h"
#include "iodriver_base.h"
#include "iodriver_impl.h"

#define CFE_PSP_IODRIVER_LOCK_TABLE_SIZE 7

CFE_PSP_MODULE_DECLARE_SIMPLE(iodriver);

static osal_id_t CFE_PSP_IODriver_Mutex_Table[CFE_PSP_IODRIVER_LOCK_TABLE_SIZE];

const CFE_PSP_IODriver_API_t CFE_PSP_IODriver_DEFAULT_API = {.DeviceCommand = NULL, .DeviceMutex = NULL};

void iodriver_Init(uint32 PspModuleId)
{
    uint32 i;
    char   TempName[OS_MAX_PATH_LEN];

    for (i = 0; i < CFE_PSP_IODRIVER_LOCK_TABLE_SIZE; ++i)
    {
        snprintf(TempName, sizeof(TempName), "DriverMutex-%02u", (unsigned int)(i + 1));
        OS_MutSemCreate(&CFE_PSP_IODriver_Mutex_Table[i], TempName, 0);
    }
}

CFE_PSP_IODriver_API_t *CFE_PSP_IODriver_GetAPI(uint32 PspModuleId)
{
    int32                   Result;
    CFE_PSP_ModuleApi_t *   API;
    CFE_PSP_IODriver_API_t *CFE_PSP_IODriver_API;

    Result = CFE_PSP_Module_GetAPIEntry(PspModuleId, &API);
    if (Result == CFE_PSP_SUCCESS && API->ModuleType == CFE_PSP_MODULE_TYPE_DEVICEDRIVER)
    {
        CFE_PSP_IODriver_API = (const CFE_PSP_IODriver_API_t *)API->ExtendedApi;
    }
    else
    {
        CFE_PSP_IODriver_API = &CFE_PSP_IODriver_DEFAULT_API;
    }

    return CFE_PSP_IODriver_API;
}

/**
 * Based on a board type and instance, determine which mutex needs to be acquired.
 * Allows some degree of parallelization by (most likely) not blocking requests to a different boards
 * that come in concurrently, but also ensuring that requests to the _same_ board will be serialized.
 * The computation here seemed to produce a decent-enough spread across the mutex table without
 * overlaps (at least with the current set of hardware)
 */
osal_id_t CFE_PSP_IODriver_GetMutex(uint32 PspModuleId, int32 DeviceHash)
{
    uint32    LookupId;
    osal_id_t ResultId;

    if (DeviceHash < 0)
    {
        /* No locking required */
        ResultId = OS_OBJECT_ID_UNDEFINED;
    }
    else
    {
        LookupId = (uint32)DeviceHash;
        if (PspModuleId != 0)
        {
            LookupId ^= PspModuleId;
        }
        ResultId = CFE_PSP_IODriver_Mutex_Table[LookupId % CFE_PSP_IODRIVER_LOCK_TABLE_SIZE];
    }

    return ResultId;
}

int32 CFE_PSP_IODriver_HashMutex(int32 StartHash, int32 Datum)
{
    Datum *= 0x10AB;
    return ((StartHash + Datum) & 0x7FFFFFFF);
}

int32 CFE_PSP_IODriver_Command(const CFE_PSP_IODriver_Location_t *Location, uint32 CommandCode,
                               CFE_PSP_IODriver_Arg_t Arg)
{
    int32                   Result;
    osal_id_t               MutexId;
    CFE_PSP_IODriver_API_t *API;

    API = CFE_PSP_IODriver_GetAPI(Location->PspModuleId);
    if (API->DeviceCommand != NULL)
    {
        if (API->DeviceMutex != NULL)
        {
            MutexId =
                CFE_PSP_IODriver_GetMutex(Location->PspModuleId, API->DeviceMutex(CommandCode, Location->SubsystemId,
                                                                                  Location->SubchannelId, Arg));
        }
        else
        {
            MutexId = OS_OBJECT_ID_UNDEFINED;
        }
        if (OS_ObjectIdDefined(MutexId))
        {
            OS_MutSemTake(MutexId);
        }
        Result = API->DeviceCommand(CommandCode, Location->SubsystemId, Location->SubchannelId, Arg);
        if (OS_ObjectIdDefined(MutexId))
        {
            OS_MutSemGive(MutexId);
        }
    }
    else
    {
        /* No command function defined - this is a driver implementation error */
        Result = CFE_PSP_ERROR_NOT_IMPLEMENTED;
    }

    return Result;
}

int32 CFE_PSP_IODriver_FindByName(const char *DriverName, uint32 *PspModuleId)
{
    int32                Result;
    CFE_PSP_ModuleApi_t *API;

    Result = CFE_PSP_Module_FindByName(DriverName, PspModuleId);
    if (Result == CFE_PSP_SUCCESS)
    {
        /*
         * Check that the module is actually registered as a device driver,
         * if not then return CFE_PSP_INVALID_MODULE_NAME instead of SUCCESS
         */
        Result = CFE_PSP_Module_GetAPIEntry(*PspModuleId, &API);
        if (Result == CFE_PSP_SUCCESS && API->ModuleType != CFE_PSP_MODULE_TYPE_DEVICEDRIVER)
        {
            Result = CFE_PSP_INVALID_MODULE_NAME;
        }
    }

    return Result;
}
