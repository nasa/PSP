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

#include "coveragetest-psp-pc-rtems.h"

#include "cfe_psp.h"

extern uint32 CFE_PSP_WatchdogValue;

/* Placeholder coverage test */
void Test_CFE_PSP_WatchdogInit(void)
{
    CFE_PSP_WatchdogInit();
}

/* Placeholder coverage test */
void Test_CFE_PSP_WatchdogEnable(void)
{
    CFE_PSP_WatchdogEnable();
}

/* Placeholder coverage test */
void Test_CFE_PSP_WatchdogDisable(void)
{
    CFE_PSP_WatchdogDisable();
}

/* Placeholder coverage test */
void Test_CFE_PSP_WatchdogService(void)
{
    CFE_PSP_WatchdogService();
}

void Test_CFE_PSP_WatchdogGet(void)
{
    UtAssert_INT32_EQ(CFE_PSP_WatchdogGet(), CFE_PSP_WatchdogValue);
}

void Test_CFE_PSP_WatchdogSet(void)
{
    uint32 WatchdogValueToSet = 42;

    CFE_PSP_WatchdogSet(WatchdogValueToSet);
    UtAssert_INT32_EQ(CFE_PSP_WatchdogValue, WatchdogValueToSet);
}
