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

#include "PCS_rtems.h"
#include "PCS_bsdnet.h"
#include "PCS_stdlib.h"
#include "PCS_stdio.h"

extern int CFE_PSP_Setup(void);

/* NOTE: The UT assert library itself defines OS_Application_Startup. To avoid conflict with the UT assert,
 * version, the unit under test is renamed to "UT_OS_Application_Startup" using a preprocessor definition. */
extern void UT_OS_Application_Startup(void);

/* Blocks of 'heap' memory for emulated calls to malloc (via PCS_malloc) in the tests */
uint32 UT_StartupBuffer[1024];
uint32 UT_MainBuffer[1024];

void Test_CFE_PSP_Setup(void)
{
    /* Nominal/Success path */
    UtAssert_INT32_EQ(CFE_PSP_Setup(), PCS_RTEMS_SUCCESSFUL);

    /* Test for printf due to error from rtems_bsdnet_initialize_network (function still returns RTEMS_SUCCESSFUL) */
    UT_SetDefaultReturnValue(UT_KEY(PCS_rtems_bsdnet_initialize_network), -1);
    UtAssert_INT32_EQ(CFE_PSP_Setup(), PCS_RTEMS_SUCCESSFUL);
    UtAssert_STUB_COUNT(PCS_printf, 1);
}

void Test_OS_Application_Startup(void)
{
    /* Set up 'heap' buffer for emulated calls to malloc */
    UT_SetDataBuffer(UT_KEY(PCS_malloc), UT_StartupBuffer, sizeof(UT_StartupBuffer), false);
    UT_OS_Application_Startup();
    UtAssert_STUB_COUNT(OS_API_Init, 1); /* Test for successful initialization (called by CFE_PSP_Main) */

    /* Cannot test for failure of CFE_PSP_Setup (it always returns RTEMS_SUCCESSFUL in the current implementation - so
     * this branch is unreachable) */
}

void Test_CFE_PSP_Main(void)
{
    /* Set up 'heap' buffer for emulated calls to malloc */
    UT_SetDataBuffer(UT_KEY(PCS_malloc), UT_MainBuffer, sizeof(UT_MainBuffer), false);

    /* Nominal/Success path */
    CFE_PSP_Main();
    UtAssert_STUB_COUNT(OS_API_Init, 1);
    /* Expect 4 x OS_printf - 3 from CFE_PSP_SetupReservedMemoryMap and 1 from CFE_PSP_InitProcessorReservedMemory */
    UtAssert_STUB_COUNT(OS_printf, 4);
    UT_ResetState(UT_KEY(OS_printf)); /* Reset so cleared for next test */

    /* Error return from OS_API_Init */
    UT_SetDefaultReturnValue(UT_KEY(OS_API_Init), OS_ERROR);
    CFE_PSP_Main();
    UtAssert_STUB_COUNT(OS_ApplicationExit, 1);
    UT_ResetState(UT_KEY(OS_printf)); /* Reset so cleared for next test */

    /* Error return from OS_FileSysAddFixedMap */
    UT_SetDefaultReturnValue(UT_KEY(OS_FileSysAddFixedMap), -1);
    CFE_PSP_Main();
    /* Expect 5 total calls to OS_printf - 3 from CFE_PSP_SetupReservedMemoryMap, 1 from status check due to
     * failure of OS_FileSysAddFixedMap, and 1 from CFE_PSP_InitProcessorReservedMemory */
    UtAssert_STUB_COUNT(OS_printf, 5);
    UT_ResetState(UT_KEY(OS_printf)); /* Reset so cleared for future tests */
}