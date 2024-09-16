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
 * Auto-Generated stub implementations for functions defined in cfe_psp_memrange_api header
 */

#include "cfe_psp_memrange_api.h"
#include "utgenstub.h"

void UT_DefaultHandler_CFE_PSP_GetCFETextSegmentInfo(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_GetKernelTextSegmentInfo(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_GetResetArea(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_GetVolatileDiskMem(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_GetCFETextSegmentInfo()
 * ----------------------------------------------------
 */
int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment, uint32 *SizeOfCFESegment)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_GetCFETextSegmentInfo, int32);

    UT_GenStub_AddParam(CFE_PSP_GetCFETextSegmentInfo, cpuaddr *, PtrToCFESegment);
    UT_GenStub_AddParam(CFE_PSP_GetCFETextSegmentInfo, uint32 *, SizeOfCFESegment);

    UT_GenStub_Execute(CFE_PSP_GetCFETextSegmentInfo, Basic, UT_DefaultHandler_CFE_PSP_GetCFETextSegmentInfo);

    return UT_GenStub_GetReturnValue(CFE_PSP_GetCFETextSegmentInfo, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_GetKernelTextSegmentInfo()
 * ----------------------------------------------------
 */
int32 CFE_PSP_GetKernelTextSegmentInfo(cpuaddr *PtrToKernelSegment, uint32 *SizeOfKernelSegment)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_GetKernelTextSegmentInfo, int32);

    UT_GenStub_AddParam(CFE_PSP_GetKernelTextSegmentInfo, cpuaddr *, PtrToKernelSegment);
    UT_GenStub_AddParam(CFE_PSP_GetKernelTextSegmentInfo, uint32 *, SizeOfKernelSegment);

    UT_GenStub_Execute(CFE_PSP_GetKernelTextSegmentInfo, Basic, UT_DefaultHandler_CFE_PSP_GetKernelTextSegmentInfo);

    return UT_GenStub_GetReturnValue(CFE_PSP_GetKernelTextSegmentInfo, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_GetResetArea()
 * ----------------------------------------------------
 */
int32 CFE_PSP_GetResetArea(cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_GetResetArea, int32);

    UT_GenStub_AddParam(CFE_PSP_GetResetArea, cpuaddr *, PtrToResetArea);
    UT_GenStub_AddParam(CFE_PSP_GetResetArea, uint32 *, SizeOfResetArea);

    UT_GenStub_Execute(CFE_PSP_GetResetArea, Basic, UT_DefaultHandler_CFE_PSP_GetResetArea);

    return UT_GenStub_GetReturnValue(CFE_PSP_GetResetArea, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_GetUserReservedArea()
 * ----------------------------------------------------
 */
int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea, uint32 *SizeOfUserArea)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_GetUserReservedArea, int32);

    UT_GenStub_AddParam(CFE_PSP_GetUserReservedArea, cpuaddr *, PtrToUserArea);
    UT_GenStub_AddParam(CFE_PSP_GetUserReservedArea, uint32 *, SizeOfUserArea);

    UT_GenStub_Execute(CFE_PSP_GetUserReservedArea, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_GetUserReservedArea, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_GetVolatileDiskMem()
 * ----------------------------------------------------
 */
int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_GetVolatileDiskMem, int32);

    UT_GenStub_AddParam(CFE_PSP_GetVolatileDiskMem, cpuaddr *, PtrToVolDisk);
    UT_GenStub_AddParam(CFE_PSP_GetVolatileDiskMem, uint32 *, SizeOfVolDisk);

    UT_GenStub_Execute(CFE_PSP_GetVolatileDiskMem, Basic, UT_DefaultHandler_CFE_PSP_GetVolatileDiskMem);

    return UT_GenStub_GetReturnValue(CFE_PSP_GetVolatileDiskMem, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_MemRangeGet()
 * ----------------------------------------------------
 */
int32 CFE_PSP_MemRangeGet(uint32 RangeNum, uint32 *MemoryType, cpuaddr *StartAddr, size_t *Size, size_t *WordSize,
                          uint32 *Attributes)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_MemRangeGet, int32);

    UT_GenStub_AddParam(CFE_PSP_MemRangeGet, uint32, RangeNum);
    UT_GenStub_AddParam(CFE_PSP_MemRangeGet, uint32 *, MemoryType);
    UT_GenStub_AddParam(CFE_PSP_MemRangeGet, cpuaddr *, StartAddr);
    UT_GenStub_AddParam(CFE_PSP_MemRangeGet, size_t *, Size);
    UT_GenStub_AddParam(CFE_PSP_MemRangeGet, size_t *, WordSize);
    UT_GenStub_AddParam(CFE_PSP_MemRangeGet, uint32 *, Attributes);

    UT_GenStub_Execute(CFE_PSP_MemRangeGet, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_MemRangeGet, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_MemRangeSet()
 * ----------------------------------------------------
 */
int32 CFE_PSP_MemRangeSet(uint32 RangeNum, uint32 MemoryType, cpuaddr StartAddr, size_t Size, size_t WordSize,
                          uint32 Attributes)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_MemRangeSet, int32);

    UT_GenStub_AddParam(CFE_PSP_MemRangeSet, uint32, RangeNum);
    UT_GenStub_AddParam(CFE_PSP_MemRangeSet, uint32, MemoryType);
    UT_GenStub_AddParam(CFE_PSP_MemRangeSet, cpuaddr, StartAddr);
    UT_GenStub_AddParam(CFE_PSP_MemRangeSet, size_t, Size);
    UT_GenStub_AddParam(CFE_PSP_MemRangeSet, size_t, WordSize);
    UT_GenStub_AddParam(CFE_PSP_MemRangeSet, uint32, Attributes);

    UT_GenStub_Execute(CFE_PSP_MemRangeSet, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_MemRangeSet, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_MemRanges()
 * ----------------------------------------------------
 */
uint32 CFE_PSP_MemRanges(void)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_MemRanges, uint32);

    UT_GenStub_Execute(CFE_PSP_MemRanges, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_MemRanges, uint32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_MemValidateRange()
 * ----------------------------------------------------
 */
int32 CFE_PSP_MemValidateRange(cpuaddr Address, size_t Size, uint32 MemoryType)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_MemValidateRange, int32);

    UT_GenStub_AddParam(CFE_PSP_MemValidateRange, cpuaddr, Address);
    UT_GenStub_AddParam(CFE_PSP_MemValidateRange, size_t, Size);
    UT_GenStub_AddParam(CFE_PSP_MemValidateRange, uint32, MemoryType);

    UT_GenStub_Execute(CFE_PSP_MemValidateRange, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_MemValidateRange, int32);
}
