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

/**
 * @file
 *
 * Auto-Generated stub implementations for functions defined in cfe_psp_watchdog_api header
 */

#include "cfe_psp_watchdog_api.h"
#include "utgenstub.h"

void UT_DefaultHandler_CFE_PSP_Panic(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_Restart(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_GetRestartType()
 * ----------------------------------------------------
 */
uint32 CFE_PSP_GetRestartType(uint32 *restartSubType)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_GetRestartType, uint32);

    UT_GenStub_AddParam(CFE_PSP_GetRestartType, uint32 *, restartSubType);

    UT_GenStub_Execute(CFE_PSP_GetRestartType, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_GetRestartType, uint32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Panic()
 * ----------------------------------------------------
 */
void CFE_PSP_Panic(int32 ErrorCode)
{
    UT_GenStub_AddParam(CFE_PSP_Panic, int32, ErrorCode);

    UT_GenStub_Execute(CFE_PSP_Panic, Basic, UT_DefaultHandler_CFE_PSP_Panic);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Restart()
 * ----------------------------------------------------
 */
void CFE_PSP_Restart(uint32 resetType)
{
    UT_GenStub_AddParam(CFE_PSP_Restart, uint32, resetType);

    UT_GenStub_Execute(CFE_PSP_Restart, Basic, UT_DefaultHandler_CFE_PSP_Restart);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_WatchdogDisable()
 * ----------------------------------------------------
 */
void CFE_PSP_WatchdogDisable(void)
{

    UT_GenStub_Execute(CFE_PSP_WatchdogDisable, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_WatchdogEnable()
 * ----------------------------------------------------
 */
void CFE_PSP_WatchdogEnable(void)
{

    UT_GenStub_Execute(CFE_PSP_WatchdogEnable, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_WatchdogGet()
 * ----------------------------------------------------
 */
uint32 CFE_PSP_WatchdogGet(void)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_WatchdogGet, uint32);

    UT_GenStub_Execute(CFE_PSP_WatchdogGet, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_WatchdogGet, uint32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_WatchdogInit()
 * ----------------------------------------------------
 */
void CFE_PSP_WatchdogInit(void)
{

    UT_GenStub_Execute(CFE_PSP_WatchdogInit, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_WatchdogService()
 * ----------------------------------------------------
 */
void CFE_PSP_WatchdogService(void)
{

    UT_GenStub_Execute(CFE_PSP_WatchdogService, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_WatchdogSet()
 * ----------------------------------------------------
 */
void CFE_PSP_WatchdogSet(uint32 WatchdogValue)
{
    UT_GenStub_AddParam(CFE_PSP_WatchdogSet, uint32, WatchdogValue);

    UT_GenStub_Execute(CFE_PSP_WatchdogSet, Basic, NULL);
}
