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
** Include section
*/
#include <stdio.h>

#include "cfe_psp.h"
#include "cfe_psp_module.h"

CFE_PSP_MODULE_DECLARE_SIMPLE(eeprom_direct);

void eeprom_direct_Init(uint32 PspModuleId)
{
    /* Inform the user that this module is in use */
    printf("CFE_PSP: Using DIRECT memory mapped EEPROM implementation\n");
}

/*
** global memory
*/

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_EepromWrite32(cpuaddr MemoryAddress, uint32 uint32Value)
{
    uint32 ret_value = CFE_PSP_SUCCESS;

    /* check 32 bit alignment  */
    if (MemoryAddress & 0x00000003)
    {
        return CFE_PSP_ERROR_ADDRESS_MISALIGNED;
    }

    /* make the Write */
    *((uint32 *)MemoryAddress) = uint32Value;

    return ret_value;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_EepromWrite16(cpuaddr MemoryAddress, uint16 uint16Value)
{
    uint32  write32;
    uint32  temp32;
    cpuaddr aligned_address;

    /*
    ** check 16 bit alignment  , check the 1st lsb
    */
    if (MemoryAddress & 0x00000001)
    {
        return CFE_PSP_ERROR_ADDRESS_MISALIGNED;
    }

    temp32 = uint16Value;

#ifdef SOFTWARE_LITTLE_BIT_ORDER
    /*
    ** Implementation for Little Endian architectures ( x86 )
    */

    /*
    ** check the 2nd lsb to see if it's the 1st or 2nd 16 bit word
    */
    if ((MemoryAddress & 0x00000002))
    {
        /*
        ** writing the 16 high bit order of 32 bit field
        */
        aligned_address = MemoryAddress - 2;
        CFE_PSP_MemRead32(aligned_address, &write32);
        write32 = (write32 & 0x0000FFFF) | (temp32 << 16);
    }
    else
    {
        /*
        ** writing the 16 low bit order of 32 bit field
        */
        aligned_address = MemoryAddress;
        CFE_PSP_MemRead32(aligned_address, &write32);
        write32 = (write32 & 0xFFFF0000) | (temp32);
    }

#else

    /*
    ** Implementation for Big Endian architectures (PPC, Coldfire )
    */
    /*
    ** check the 2nd lsb to see if it's the 1st or 2nd 16 bit word
    */
    if ((MemoryAddress & 0x00000002))
    {
        /*
        ** writing the 16 high bit order of 32 bit field
        */
        aligned_address = MemoryAddress - 2;
        CFE_PSP_MemRead32(aligned_address, &write32);
        write32 = (write32 & 0xFFFF0000) | (temp32);
    }
    else
    {
        /*
        ** writing the 16 low bit order of 32 bit field
        */
        aligned_address = MemoryAddress;
        CFE_PSP_MemRead32(aligned_address, &write32);
        write32 = (write32 & 0x0000FFFF) | (temp32 << 16);
    }
#endif

    return CFE_PSP_EepromWrite32(aligned_address, write32);
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_EepromWrite8(cpuaddr MemoryAddress, uint8 ByteValue)
{
    cpuaddr aligned_address;
    uint16  write16, temp16;

    temp16 = ByteValue;

#ifdef SOFTWARE_LITTLE_BIT_ORDER
    /*
    ** Implementation for Little Endian architectures ( x86 )
    */
    /*
    ** check the 1st lsb
    */
    if (MemoryAddress & 0x00000001)
    {
        /*
        ** writing the 8 high bit order of 16 bit field
        */
        aligned_address = MemoryAddress - 1;
        CFE_PSP_MemRead16(aligned_address, &write16);
        write16 = (write16 & 0x00FF) | (temp16 << 8);
    }
    else
    {
        /*
        ** writing the 8 low bit order of 16 bit field
        */
        aligned_address = MemoryAddress;
        CFE_PSP_MemRead16(aligned_address, &write16);
        write16 = (temp16) | (write16 & 0xFF00);
    }
#else

    /*
    ** Implementation for Big Endian architectures (PPC, Coldfire )
    */

    /*
    ** check the 1st lsb
    */
    if (MemoryAddress & 0x00000001)
    {
        /*
        ** writing the 8 high bit order of 16 bit field
        */
        aligned_address = MemoryAddress - 1;
        CFE_PSP_MemRead16(aligned_address, &write16);
        write16 = (write16 & 0xFF00) | (temp16);
    }
    else
    {
        /*
        ** writing the 8 low bit order of 16 bit field
        */
        aligned_address = MemoryAddress;
        CFE_PSP_MemRead16(aligned_address, &write16);
        write16 = (temp16 << 8) | (write16 & 0x00FF);
    }

#endif

    return CFE_PSP_EepromWrite16(aligned_address, write16);
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_EepromWriteEnable(uint32 Bank)
{
    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_EepromWriteDisable(uint32 Bank)
{
    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_EepromPowerUp(uint32 Bank)
{
    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_EepromPowerDown(uint32 Bank)
{
    return CFE_PSP_SUCCESS;
}
