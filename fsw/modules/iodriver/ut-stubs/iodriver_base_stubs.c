/*
 *  Copyright (c) 2015, United States government as represented by the
 *  administrator of the National Aeronautics Space Administration.
 *  All rights reserved. This software was created at NASA Glenn
 *  Research Center pursuant to government contracts.
 */

/**
 * @file
 *
 * Auto-Generated stub implementations for functions defined in iodriver_base header
 */

#include "iodriver_base.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_IODriver_Command()
 * ----------------------------------------------------
 */
int32 CFE_PSP_IODriver_Command(const CFE_PSP_IODriver_Location_t *Location, uint32 CommandCode,
                               CFE_PSP_IODriver_Arg_t Arg)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_IODriver_Command, int32);

    UT_GenStub_AddParam(CFE_PSP_IODriver_Command, const CFE_PSP_IODriver_Location_t *, Location);
    UT_GenStub_AddParam(CFE_PSP_IODriver_Command, uint32, CommandCode);
    UT_GenStub_AddParam(CFE_PSP_IODriver_Command, CFE_PSP_IODriver_Arg_t, Arg);

    UT_GenStub_Execute(CFE_PSP_IODriver_Command, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_IODriver_Command, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_IODriver_FindByName()
 * ----------------------------------------------------
 */
int32 CFE_PSP_IODriver_FindByName(const char *DriverName, uint32 *PspModuleId)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_IODriver_FindByName, int32);

    UT_GenStub_AddParam(CFE_PSP_IODriver_FindByName, const char *, DriverName);
    UT_GenStub_AddParam(CFE_PSP_IODriver_FindByName, uint32 *, PspModuleId);

    UT_GenStub_Execute(CFE_PSP_IODriver_FindByName, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_IODriver_FindByName, int32);
}
