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
** File: ut_bsp_stubs.c
**
** Purpose:
** Unit test stubs for BSP routines
**
** Notes:
** Minimal work is done, only what is required for unit testing
**
*/

/*
** Includes
*/

#include "cfe_psp.h"
#include "utstubs.h"
#include <string.h>

/*
** Functions
*/

void UT_DefaultHandler_CFE_PSP_GetTime(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* void CFE_PSP_GetTime(OS_time_t *LocalTime) */
    OS_time_t *LocalTime = UT_Hook_GetArgValueByName(Context, "LocalTime", OS_time_t *);
    int32      status;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        if (UT_Stub_CopyToLocal(UT_KEY(CFE_PSP_GetTime), (uint8 *)LocalTime, sizeof(*LocalTime)) < sizeof(*LocalTime))
        {
            *LocalTime = OS_TimeAssembleFromNanoseconds(100, 200000);
        }
    }
}

void UT_DefaultHandler_CFE_PSP_GetTimerTicksPerSecond(void *UserObj, UT_EntryKey_t FuncKey,
                                                      const UT_StubContext_t *Context)
{
    /* uint32 CFE_PSP_GetTimerTicksPerSecond(void) */
    uint32 retval;
    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        retval = 2000;
        UT_Stub_SetReturnValue(FuncKey, retval);
    }
}

void UT_DefaultHandler_CFE_PSP_GetTimerLow32Rollover(void *UserObj, UT_EntryKey_t FuncKey,
                                                     const UT_StubContext_t *Context)
{
    /* uint32 CFE_PSP_GetTimerLow32Rollover(void) */
    uint32 retval;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        retval = 100000;
        UT_Stub_SetReturnValue(FuncKey, retval);
    }
}
