/*
 *  Copyright (c) 2015, United States government as represented by the
 *  administrator of the National Aeronautics Space Administration.
 *  All rights reserved. This software was created at NASA Glenn
 *  Research Center pursuant to government contracts.
 */

/**
 * @file
 *
 * Auto-Generated stub implementations for functions defined in iodriver_impl header
 */

#include "iodriver_impl.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_IODriver_GetMutex()
 * ----------------------------------------------------
 */
osal_id_t CFE_PSP_IODriver_GetMutex(uint32 PspModuleId, int32 DeviceHash)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_IODriver_GetMutex, osal_id_t);

    UT_GenStub_AddParam(CFE_PSP_IODriver_GetMutex, uint32, PspModuleId);
    UT_GenStub_AddParam(CFE_PSP_IODriver_GetMutex, int32, DeviceHash);

    UT_GenStub_Execute(CFE_PSP_IODriver_GetMutex, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_IODriver_GetMutex, osal_id_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_IODriver_HashMutex()
 * ----------------------------------------------------
 */
int32 CFE_PSP_IODriver_HashMutex(int32 StartHash, int32 Datum)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_IODriver_HashMutex, int32);

    UT_GenStub_AddParam(CFE_PSP_IODriver_HashMutex, int32, StartHash);
    UT_GenStub_AddParam(CFE_PSP_IODriver_HashMutex, int32, Datum);

    UT_GenStub_Execute(CFE_PSP_IODriver_HashMutex, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_IODriver_HashMutex, int32);
}
