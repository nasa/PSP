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
** File   :	cfe_psp_memrange.c
**
** Author :	Alan Cudmore
**
** Purpose:
**		   This file contains the memory range functions for the cFE Platform Support Package.
**       The memory range is a table of valid memory address ranges maintained by the cFE.
**
**
*/

/*
** Include section
*/

#include "cfe_psp.h"
#include "cfe_psp_memory.h"

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_MemValidateRange(cpuaddr Address, size_t Size, uint32 MemoryType)
{
    cpuaddr             StartAddressToTest = Address;
    cpuaddr             EndAddressToTest   = Address + Size - 1;
    cpuaddr             StartAddressInTable;
    cpuaddr             EndAddressInTable;
    uint32              TypeInTable;
    int32               ReturnCode = CFE_PSP_INVALID_MEM_ADDR;
    size_t              i;
    CFE_PSP_MemTable_t *SysMemPtr;

    /*
    ** Before searching table, do a preliminary parameter validation
    */
    if (MemoryType != CFE_PSP_MEM_ANY && MemoryType != CFE_PSP_MEM_RAM && MemoryType != CFE_PSP_MEM_EEPROM)
    {
        return CFE_PSP_INVALID_MEM_TYPE;
    }

    if (EndAddressToTest < StartAddressToTest)
    {
        return CFE_PSP_INVALID_MEM_RANGE;
    }

    SysMemPtr = CFE_PSP_ReservedMemoryMap.SysMemoryTable;
    for (i = 0; i < CFE_PSP_MEM_TABLE_SIZE; i++)
    {
        /*
        ** Only look at valid memory table entries
        */
        if (SysMemPtr->MemoryType != CFE_PSP_MEM_INVALID)
        {
            StartAddressInTable = SysMemPtr->StartAddr;
            EndAddressInTable   = SysMemPtr->StartAddr + SysMemPtr->Size - 1;
            TypeInTable         = SysMemPtr->MemoryType;

            /*
            ** Step 1: Get the Address to Fit within the range
            */
            if ((StartAddressToTest >= StartAddressInTable) && (StartAddressToTest <= EndAddressInTable))
            {
                /*
                ** Step 2: Does the End Address Fit within the Range?
                **         should not have to test the lower address,
                **         since the StartAddressToTest is already in the range.
                **         Can it be fooled by overflowing the 32 bit int?
                */
                if (EndAddressToTest <= EndAddressInTable)
                {
                    /*
                    ** Step 3: Is the type OK?
                    */
                    if (MemoryType == CFE_PSP_MEM_ANY)
                    {
                        ReturnCode = CFE_PSP_SUCCESS;
                        break; /* The range is valid, break out of the loop */
                    }
                    else if (MemoryType == CFE_PSP_MEM_RAM && TypeInTable == CFE_PSP_MEM_RAM)
                    {
                        ReturnCode = CFE_PSP_SUCCESS;
                        break; /* The range is valid, break out of the loop */
                    }
                    else if (MemoryType == CFE_PSP_MEM_EEPROM && TypeInTable == CFE_PSP_MEM_EEPROM)
                    {
                        ReturnCode = CFE_PSP_SUCCESS;
                        break; /* The range is valid, break out of the loop */
                    }
                    else
                    {
                        ReturnCode = CFE_PSP_INVALID_MEM_TYPE;
                        /* The range is not valid, move to the next entry */
                    }
                }
                else
                {
                    ReturnCode = CFE_PSP_INVALID_MEM_RANGE;
                    /* The range is not valid, move to the next entry */
                }
            }
            else
            {
                ReturnCode = CFE_PSP_INVALID_MEM_ADDR;
                /* The range is not valid, move to the next entry */
            }
        } /* End if MemoryType != CFE_PSP_MEM_INVALID */

        ++SysMemPtr;

    } /* End for */
    return ReturnCode;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
uint32 CFE_PSP_MemRanges(void)
{
    return CFE_PSP_MEM_TABLE_SIZE;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_MemRangeSet(uint32 RangeNum, uint32 MemoryType, cpuaddr StartAddr, size_t Size, size_t WordSize,
                          uint32 Attributes)
{
    CFE_PSP_MemTable_t *SysMemPtr;

    if (RangeNum >= CFE_PSP_MEM_TABLE_SIZE)
    {
        return CFE_PSP_INVALID_MEM_RANGE;
    }

    if ((MemoryType != CFE_PSP_MEM_RAM) && (MemoryType != CFE_PSP_MEM_EEPROM))
    {
        return CFE_PSP_INVALID_MEM_TYPE;
    }

    if ((WordSize != CFE_PSP_MEM_SIZE_BYTE) && (WordSize != CFE_PSP_MEM_SIZE_WORD) &&
        (WordSize != CFE_PSP_MEM_SIZE_DWORD))
    {
        return CFE_PSP_INVALID_MEM_WORDSIZE;
    }

    if ((Attributes != CFE_PSP_MEM_ATTR_READ) && (Attributes != CFE_PSP_MEM_ATTR_WRITE) &&
        (Attributes != CFE_PSP_MEM_ATTR_READWRITE))
    {
        return CFE_PSP_INVALID_MEM_ATTR;
    }

    /*
    ** Parameters check out, add the range
    */
    SysMemPtr = &CFE_PSP_ReservedMemoryMap.SysMemoryTable[RangeNum];

    SysMemPtr->MemoryType = MemoryType;
    SysMemPtr->StartAddr  = StartAddr;
    SysMemPtr->Size       = Size;
    SysMemPtr->WordSize   = WordSize;
    SysMemPtr->Attributes = Attributes;

    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_MemRangeGet(uint32 RangeNum, uint32 *MemoryType, cpuaddr *StartAddr, size_t *Size, size_t *WordSize,
                          uint32 *Attributes)
{
    CFE_PSP_MemTable_t *SysMemPtr;

    if (MemoryType == NULL || StartAddr == NULL || Size == NULL || WordSize == NULL || Attributes == NULL)
    {
        return CFE_PSP_INVALID_POINTER;
    }

    if (RangeNum >= CFE_PSP_MEM_TABLE_SIZE)
    {
        return CFE_PSP_INVALID_MEM_RANGE;
    }

    SysMemPtr = &CFE_PSP_ReservedMemoryMap.SysMemoryTable[RangeNum];

    *MemoryType = SysMemPtr->MemoryType;
    *StartAddr  = SysMemPtr->StartAddr;
    *Size       = SysMemPtr->Size;
    *WordSize   = SysMemPtr->WordSize;
    *Attributes = SysMemPtr->Attributes;

    return CFE_PSP_SUCCESS;
}
