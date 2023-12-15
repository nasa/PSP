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

#include "cfe_psp.h"

#include "coveragetest-psp-pc-rtems.h"

#include "PCS_stdlib.h"
#include "PCS_cfe_configdata.h"

void Test_CFE_PSP_Restart(void)
{
    CFE_PSP_Restart(CFE_PSP_RST_TYPE_PROCESSOR);
    UtAssert_STUB_COUNT(PCS_exit, 1);
    UT_ResetState(UT_KEY(PCS_exit)); /* Reset so cleared for next test */

    CFE_PSP_Restart(CFE_PSP_RST_TYPE_POWERON);
    UtAssert_STUB_COUNT(PCS_exit, 1);
}

void Test_CFE_PSP_Panic(void)
{
    CFE_PSP_Panic(0);
    UtAssert_STUB_COUNT(OS_ApplicationExit, 1);
}

/* Placeholder coverage test */
void Test_CFE_PSP_FlushCaches(void)
{
    CFE_PSP_FlushCaches(0, NULL, 0);
    CFE_PSP_FlushCaches(1, NULL, 0);
}

void Test_CFE_PSP_GetProcessorId(void)
{
    UtAssert_INT32_EQ(CFE_PSP_GetProcessorId(), PCS_CONFIG_CPUNUMBER);
}

void Test_CFE_PSP_GetSpacecraftId(void)
{
    UtAssert_INT32_EQ(CFE_PSP_GetSpacecraftId(), PCS_CONFIG_SPACECRAFT);
}

void Test_CFE_PSP_GetProcessorName(void)
{
    UtAssert_STRINGBUF_EQ(CFE_PSP_GetProcessorName(), UTASSERT_STRINGBUF_NULL_TERM, PCS_CONFIG_CPUNAME,
                          UTASSERT_STRINGBUF_NULL_TERM);
}