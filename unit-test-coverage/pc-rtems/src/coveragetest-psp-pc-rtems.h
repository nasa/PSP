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

#ifndef COVERAGETEST_PSP_PC_RTEMS_H
#define COVERAGETEST_PSP_PC_RTEMS_H

#include "utassert.h"
#include "uttest.h"
#include "utstubs.h"

#include "coveragetest-psp-shared.h"

#define ADD_TEST(test) UtTest_Add((Test_##test), Psp_Test_Setup, Psp_Test_Teardown, #test)

void Psp_Test_Setup(void);
void Psp_Test_Teardown(void);

/* Coverage test cases for cfs_psp_exception.c */
void Test_CFE_PSP_AttachExceptions(void);
void Test_CFE_PSP_ExceptionGetSummary_Impl(void);
void Test_CFE_PSP_SetDefaultExceptionEnvironment(void);

/* Coverage test cases for cfs_psp_memory.c */
void Test_CFE_PSP_GetCDSSize(void);
void Test_CFE_PSP_WriteToCDS(void);
void Test_CFE_PSP_ReadFromCDS(void);
void Test_CFE_PSP_GetResetArea(void);
void Test_CFE_PSP_GetUserReservedArea(void);
void Test_CFE_PSP_GetVolatileDiskMem(void);
void Test_CFE_PSP_SetupReservedMemoryMap(void);
void Test_CFE_PSP_InitProcessorReservedMemory(void);
void Test_CFE_PSP_GetKernelTextSegmentInfo(void);
void Test_CFE_PSP_GetCFETextSegmentInfo(void);

/* Coverage test cases for cfs_psp_ssr.c */
void Test_CFE_PSP_InitSSR(void);

/* Coverage test cases for cfs_psp_start.c */
void Test_CFE_PSP_Setup(void);
void Test_OS_Application_Startup(void);
void Test_CFE_PSP_Main(void);

/* Coverage test cases for cfs_psp_support.c */
void Test_CFE_PSP_Restart(void);
void Test_CFE_PSP_Panic(void);
void Test_CFE_PSP_FlushCaches(void);
void Test_CFE_PSP_GetProcessorId(void);
void Test_CFE_PSP_GetSpacecraftId(void);
void Test_CFE_PSP_GetProcessorName(void);

/* Coverage test cases for cfs_psp_watchdog.c */
void Test_CFE_PSP_WatchdogInit(void);
void Test_CFE_PSP_WatchdogEnable(void);
void Test_CFE_PSP_WatchdogDisable(void);
void Test_CFE_PSP_WatchdogService(void);
void Test_CFE_PSP_WatchdogGet(void);
void Test_CFE_PSP_WatchdogSet(void);

#endif
