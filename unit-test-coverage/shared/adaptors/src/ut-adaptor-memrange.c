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
 * \ingroup  adaptors
 *
 */

#include "ut-adaptor-memrange.h"
#include "cfe_psp_config.h"
#include "cfe_psp_memory.h"

uint32 UT_Get_MemRange_MaxEntries(void)
{
    return CFE_PSP_MEM_TABLE_SIZE;
}

void UT_ClearMemRangeTable(void)
{
    memset(CFE_PSP_ReservedMemoryMap.SysMemoryTable, 0, sizeof(CFE_PSP_ReservedMemoryMap.SysMemoryTable));
}

void UT_SetupMemRangeTable(uint32 EntryNum, uint32 MemType, cpuaddr StartAddr, size_t Size, uint32 WordSize)
{
    CFE_PSP_MemTable_t *SysMemPtr;

    SysMemPtr = &CFE_PSP_ReservedMemoryMap.SysMemoryTable[EntryNum];

    SysMemPtr->MemoryType = MemType;
    SysMemPtr->StartAddr  = StartAddr;
    SysMemPtr->WordSize   = WordSize;
    SysMemPtr->Size       = Size;
}