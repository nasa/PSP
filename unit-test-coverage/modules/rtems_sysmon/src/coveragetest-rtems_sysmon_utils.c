/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/*
 *
 *    Copyright (c) 2025, United States government as represented by the
 *    administrator of the National Aeronautics Space Administration.
 *    All rights reserved. This software was created at NASA Goddard
 *    Space Flight Center pursuant to government contracts.
 *
 *    This is governed by the NASA Open Source Agreement and may be used,
 *    distributed and modified only according to the terms of that agreement.
 *
 */

/**
 * \file
 * \ingroup  modules
 *
 * utils for rtems_sysmon coverage test
 */

#include "coveragetest-rtems_sysmon_utils.h"

void ModuleTest_ResetState(void)
{
    memset(&rtems_sysmon_global, 0, sizeof(rtems_sysmon_global));
}

/* Hook */
void UT_TaskDelay_Hook(void *UserObj)
{
    int *DelayCounter                       = UserObj;
    rtems_sysmon_global.cpu_load.should_run = false;

    (*DelayCounter)++;
}

void UT_ThreadGetName_Hook(void *UserObj, int32 StubRetcode, uint32 CallCount, const UT_StubContext_t *Context)
{
    int i;

    char * Name = UT_Hook_GetArgValueByName(Context, "buffer", char *);
    UT_ThreadGetNameData_t * Data = (UT_ThreadGetNameData_t *) UserObj;

    for (i = 0; i < Data->Size; i++)
    {
        Name[i] = Data->Name[i];
    }
}

void UT_TimestampDivide_Hook(void *UserObj, int32 StubRetcode, uint32 CallCount, const UT_StubContext_t *Context)
{

    UT_TimeDivideData_t * TimeDivideData = (UT_TimeDivideData_t *) UserObj;

    uint32_t * IntValue = UT_Hook_GetArgValueByName(Context, "_ival_percentage", uint32_t *);
    uint32_t * FraValue = UT_Hook_GetArgValueByName(Context, "_fval_percentage", uint32_t *);
    int64_t *  IdleUptimeElapsed = UT_Hook_GetArgValueByName(Context, "_lhs", int64_t *);
    int64_t *  TotalElapsed = UT_Hook_GetArgValueByName(Context, "_rhs", int64_t *);

    *IntValue = TimeDivideData->IntValue;
    *FraValue = TimeDivideData->FraValue;
    *IdleUptimeElapsed = TimeDivideData->IdleUptimeElapsed;
    *TotalElapsed = TimeDivideData->TotalElapsed;
}