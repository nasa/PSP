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
#include "PCS_stdlib.h"

extern int32 CFE_PSP_InitProcessorReservedMemory(uint32 ResetType);
extern void  CFE_PSP_SetupReservedMemoryMap(void);

/* Blocks of 'heap' memory for emulated calls to malloc (via PCS_malloc) in the tests */
uint32 UT_MemoryMapBuffer[1024];
uint32 UT_TooSmallMemoryMapBuffer[1];

void Test_CFE_PSP_GetCDSSize(void)
{
    uint32 SizeOfCDS;

    /* Test NULL pointer guard */
    UtAssert_INT32_EQ(CFE_PSP_GetCDSSize(NULL), OS_ERROR);

    /* Nominal/success path */
    UtAssert_INT32_EQ(CFE_PSP_GetCDSSize(&SizeOfCDS), OS_SUCCESS);
}

void Test_CFE_PSP_WriteToCDS(void)
{
    uint32 CDSOffset = 8;
    uint32 NumBytes  = 8;

    /* Test NULL pointer guard */
    UtAssert_INT32_EQ(CFE_PSP_WriteToCDS(NULL, CDSOffset, NumBytes), OS_ERROR);
}

void Test_CFE_PSP_ReadFromCDS(void)
{
    uint32 CDSOffset = 8;
    uint32 NumBytes  = 8;

    /* Test NULL pointer guard */
    UtAssert_INT32_EQ(CFE_PSP_ReadFromCDS(NULL, CDSOffset, NumBytes), OS_ERROR);
}

void Test_CFE_PSP_GetResetArea(void)
{
    cpuaddr PtrToResetArea;
    uint32  SizeOfResetArea;

    /* Test both NULL pointer guards */
    UtAssert_INT32_EQ(CFE_PSP_GetResetArea(NULL, &SizeOfResetArea), OS_ERROR);
    UtAssert_INT32_EQ(CFE_PSP_GetResetArea(&PtrToResetArea, NULL), OS_ERROR);

    /* Nominal/success path */
    UtAssert_INT32_EQ(CFE_PSP_GetResetArea(&PtrToResetArea, &SizeOfResetArea), OS_SUCCESS);
}

void Test_CFE_PSP_GetUserReservedArea(void)
{
    cpuaddr PtrToUserArea;
    uint32  SizeOfUserArea;

    /* Test both NULL pointer guards */
    UtAssert_INT32_EQ(CFE_PSP_GetUserReservedArea(NULL, &SizeOfUserArea), OS_ERROR);
    UtAssert_INT32_EQ(CFE_PSP_GetUserReservedArea(&PtrToUserArea, NULL), OS_ERROR);

    /* Nominal/success path */
    UtAssert_INT32_EQ(CFE_PSP_GetUserReservedArea(&PtrToUserArea, &SizeOfUserArea), OS_SUCCESS);
}

void Test_CFE_PSP_GetVolatileDiskMem(void)
{
    cpuaddr PtrToVolDisk;
    uint32  SizeOfVolDisk;

    /* Test both NULL pointer guards */
    UtAssert_INT32_EQ(CFE_PSP_GetVolatileDiskMem(NULL, &SizeOfVolDisk), OS_ERROR);
    UtAssert_INT32_EQ(CFE_PSP_GetVolatileDiskMem(&PtrToVolDisk, NULL), OS_ERROR);

    /* Nominal/success path */
    UtAssert_INT32_EQ(CFE_PSP_GetVolatileDiskMem(&PtrToVolDisk, &SizeOfVolDisk), OS_SUCCESS);
}

void Test_CFE_PSP_SetupReservedMemoryMap(void)
{
    /* Test NULL ReservedMemBlock.BlockPtr path and early abort due to failure of malloc with a too-small heap */
    UT_SetDataBuffer(UT_KEY(PCS_malloc), UT_TooSmallMemoryMapBuffer, sizeof(UT_TooSmallMemoryMapBuffer), false);
    CFE_PSP_SetupReservedMemoryMap();
    UtAssert_STUB_COUNT(PCS_abort, 1);
    UT_ResetState(UT_KEY(PCS_malloc)); /* Reset so cleared for next test */
    UT_ResetState(UT_KEY(OS_printf));  /* Reset so cleared for next test */

    /* Nominal/success path with sufficiently sized 'heap' for emulated call to malloc */
    UT_SetDataBuffer(UT_KEY(PCS_malloc), UT_MemoryMapBuffer, sizeof(UT_MemoryMapBuffer), false);
    CFE_PSP_SetupReservedMemoryMap();
    UtAssert_STUB_COUNT(OS_printf, 3); /* 3 calls to OS_printf along nominal path in CFE_PSP_SetupReservedMemoryMap */
}

void Test_CFE_PSP_InitProcessorReservedMemory(void)
{
    /* Always returns CFE_PSP_SUCCESS */
    UtAssert_INT32_EQ(CFE_PSP_InitProcessorReservedMemory(CFE_PSP_RST_TYPE_POWERON), CFE_PSP_SUCCESS);
}

void Test_CFE_PSP_GetKernelTextSegmentInfo(void)
{
    cpuaddr PtrToKernelSegment;
    uint32  SizeOfKernelSegment;

    /* Test both NULL pointer guards */
    UtAssert_INT32_EQ(CFE_PSP_GetKernelTextSegmentInfo(NULL, &SizeOfKernelSegment), OS_ERROR);
    UtAssert_INT32_EQ(CFE_PSP_GetKernelTextSegmentInfo(&PtrToKernelSegment, NULL), OS_ERROR);

    /* Nominal/success path */
    UtAssert_INT32_EQ(CFE_PSP_GetKernelTextSegmentInfo(&PtrToKernelSegment, &SizeOfKernelSegment), OS_SUCCESS);
}

void Test_CFE_PSP_GetCFETextSegmentInfo(void)
{
    cpuaddr PtrToCFESegment;
    uint32  SizeOfCFESegment;

    /* Test NULL pointer guard */
    UtAssert_INT32_EQ(CFE_PSP_GetCFETextSegmentInfo(&PtrToCFESegment, NULL), OS_ERROR);

    /* Nominal/success path */
    UtAssert_INT32_EQ(CFE_PSP_GetCFETextSegmentInfo(&PtrToCFESegment, &SizeOfCFESegment), OS_SUCCESS);
}