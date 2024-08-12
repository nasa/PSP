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
 *    Copyright (c) 2020, United States government as represented by the
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
 * \ingroup  vxworks
 */

#include "utassert.h"
#include "utstubs.h"

#include "ut-adaptor-memrange.h"
#include "cfe_psp_memrange_api.h"

void Test_CFE_PSP_MemValidateRange(void)
{
    /* Test Case For:
     * int32 CFE_PSP_MemValidateRange(cpuaddr Address, size_t Size, uint32 MemoryType)
     */
    UT_ClearMemRangeTable();

    UtAssert_INT32_EQ(CFE_PSP_MemValidateRange(0, 32, 0), CFE_PSP_INVALID_MEM_TYPE);
    UtAssert_INT32_EQ(CFE_PSP_MemValidateRange(-1, 32, CFE_PSP_MEM_RAM), CFE_PSP_INVALID_MEM_RANGE);
    UtAssert_INT32_EQ(CFE_PSP_MemValidateRange(0, 32, CFE_PSP_MEM_RAM), CFE_PSP_INVALID_MEM_ADDR);
    UtAssert_INT32_EQ(CFE_PSP_MemValidateRange(0, 32, CFE_PSP_MEM_EEPROM), CFE_PSP_INVALID_MEM_ADDR);
    UtAssert_INT32_EQ(CFE_PSP_MemValidateRange(0, 32, CFE_PSP_MEM_ANY), CFE_PSP_INVALID_MEM_ADDR);

    UT_SetupMemRangeTable(1, CFE_PSP_MEM_RAM, 0, 0x1000, 4);
    UT_SetupMemRangeTable(2, CFE_PSP_MEM_INVALID, 0x1000, 0x1000, 4);
    UT_SetupMemRangeTable(3, CFE_PSP_MEM_EEPROM, 0x2000, 0x1000, 4);
    UtAssert_INT32_EQ(CFE_PSP_MemValidateRange(0, 0x100, CFE_PSP_MEM_RAM), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_MemValidateRange(0x100, 0x100, CFE_PSP_MEM_ANY), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_MemValidateRange(0x200, 0x100, CFE_PSP_MEM_EEPROM), CFE_PSP_INVALID_MEM_ADDR);
    UtAssert_INT32_EQ(CFE_PSP_MemValidateRange(0x2000, 0x100, CFE_PSP_MEM_RAM), CFE_PSP_INVALID_MEM_ADDR);
    UtAssert_INT32_EQ(CFE_PSP_MemValidateRange(0x2000, 0x100, CFE_PSP_MEM_EEPROM), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_MemValidateRange(0x1000, 0x100, CFE_PSP_MEM_RAM), CFE_PSP_INVALID_MEM_ADDR);

    /* Validate a range that crosses from one region into another */
    UtAssert_INT32_EQ(CFE_PSP_MemValidateRange(0x800, 0x1000, CFE_PSP_MEM_RAM), CFE_PSP_INVALID_MEM_ADDR);
}

void Test_CFE_PSP_MemRanges(void)
{
    /* Test Case For:
     * uint32 CFE_PSP_MemRanges(void)
     */
    UtAssert_UINT32_EQ(CFE_PSP_MemRanges(), UT_Get_MemRange_MaxEntries());
}

void Test_CFE_PSP_MemRangeSet(void)
{
    /* Test Case For:
     * int32 CFE_PSP_MemRangeSet(uint32 RangeNum, uint32 MemoryType, cpuaddr StartAddr, size_t Size, size_t WordSize,
     * uint32 Attributes)
     */
    UT_ClearMemRangeTable();
    UtAssert_INT32_EQ(CFE_PSP_MemRangeSet(UINT32_MAX, CFE_PSP_MEM_RAM, 0, 32, 1, 0), CFE_PSP_INVALID_MEM_RANGE);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeSet(0, 0, 0, 32, 1, 0), CFE_PSP_INVALID_MEM_TYPE);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeSet(0, CFE_PSP_MEM_RAM, 0, 32, 1, 0), CFE_PSP_INVALID_MEM_ATTR);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeSet(0, CFE_PSP_MEM_RAM, 0, 32, 1, 0), CFE_PSP_INVALID_MEM_ATTR);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeSet(0, CFE_PSP_MEM_RAM, 0, 32, 2, CFE_PSP_MEM_ATTR_READWRITE), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeSet(0, CFE_PSP_MEM_RAM, 0, 32, 4, CFE_PSP_MEM_ATTR_READWRITE), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeSet(0, CFE_PSP_MEM_RAM, 0, 32, 8, CFE_PSP_MEM_ATTR_READWRITE),
                      CFE_PSP_INVALID_MEM_WORDSIZE);

    UtAssert_INT32_EQ(CFE_PSP_MemRangeSet(0, CFE_PSP_MEM_EEPROM, 32, 32, 4, CFE_PSP_MEM_ATTR_WRITE), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeSet(0, CFE_PSP_MEM_EEPROM, 32, 32, 4, CFE_PSP_MEM_ATTR_READ), CFE_PSP_SUCCESS);
}

void Test_CFE_PSP_MemRangeGet(void)
{
    /* Test Case For:
     * int32 CFE_PSP_MemRangeGet(uint32 RangeNum, uint32 *MemoryType, cpuaddr *StartAddr, size_t *Size, size_t
     * *WordSize, uint32 *Attributes)
     */
    uint32  MemType;
    cpuaddr StartAddr;
    size_t  MemSize;
    size_t  WordSize;
    uint32  Attribs;

    UT_ClearMemRangeTable();
    UtAssert_INT32_EQ(CFE_PSP_MemRangeGet(UINT32_MAX, &MemType, &StartAddr, &MemSize, &WordSize, &Attribs),
                      CFE_PSP_INVALID_MEM_RANGE);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeGet(0, NULL, &StartAddr, &MemSize, &WordSize, &Attribs), CFE_PSP_INVALID_POINTER);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeGet(0, &MemType, NULL, &MemSize, &WordSize, &Attribs), CFE_PSP_INVALID_POINTER);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeGet(0, &MemType, &StartAddr, NULL, &WordSize, &Attribs), CFE_PSP_INVALID_POINTER);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeGet(0, &MemType, &StartAddr, &MemSize, NULL, &Attribs), CFE_PSP_INVALID_POINTER);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeGet(0, &MemType, &StartAddr, &MemSize, &WordSize, NULL), CFE_PSP_INVALID_POINTER);
    UtAssert_INT32_EQ(CFE_PSP_MemRangeGet(0, &MemType, &StartAddr, &MemSize, &WordSize, &Attribs), CFE_PSP_SUCCESS);
}
