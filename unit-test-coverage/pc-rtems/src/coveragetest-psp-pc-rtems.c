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

void Psp_Test_Setup(void)
{
    UT_ResetState(0);
}

void Psp_Test_Teardown(void) {}

void UtTest_Setup(void)
{
    /* Coverage test cases for cfs_psp_exception.c */
    ADD_TEST(CFE_PSP_AttachExceptions);
    ADD_TEST(CFE_PSP_ExceptionGetSummary_Impl);
    ADD_TEST(CFE_PSP_SetDefaultExceptionEnvironment);

    /* Coverage test cases for cfs_psp_memory.c */
    ADD_TEST(CFE_PSP_GetCDSSize);
    ADD_TEST(CFE_PSP_WriteToCDS);
    ADD_TEST(CFE_PSP_ReadFromCDS);
    ADD_TEST(CFE_PSP_GetResetArea);
    ADD_TEST(CFE_PSP_GetUserReservedArea);
    ADD_TEST(CFE_PSP_GetVolatileDiskMem);
    ADD_TEST(CFE_PSP_SetupReservedMemoryMap);
    ADD_TEST(CFE_PSP_InitProcessorReservedMemory);
    ADD_TEST(CFE_PSP_GetKernelTextSegmentInfo);
    ADD_TEST(CFE_PSP_GetCFETextSegmentInfo);

    /* Coverage test cases for cfs_psp_ssr.c */
    ADD_TEST(CFE_PSP_InitSSR);

    /* Coverage test cases for cfs_psp_start.c */
    ADD_TEST(CFE_PSP_Setup);
    ADD_TEST(OS_Application_Startup);
    ADD_TEST(CFE_PSP_Main);

    /* Coverage test cases for cfs_psp_support.c */
    ADD_TEST(CFE_PSP_Restart);
    ADD_TEST(CFE_PSP_Panic);
    ADD_TEST(CFE_PSP_FlushCaches);
    ADD_TEST(CFE_PSP_GetProcessorId);
    ADD_TEST(CFE_PSP_GetSpacecraftId);
    ADD_TEST(CFE_PSP_GetProcessorName);

    /* Coverage test cases for cfs_psp_watchdog.c */
    ADD_TEST(CFE_PSP_WatchdogInit);
    ADD_TEST(CFE_PSP_WatchdogEnable);
    ADD_TEST(CFE_PSP_WatchdogDisable);
    ADD_TEST(CFE_PSP_WatchdogService);
    ADD_TEST(CFE_PSP_WatchdogGet);
    ADD_TEST(CFE_PSP_WatchdogSet);
}
