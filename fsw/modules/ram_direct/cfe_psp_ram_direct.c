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
 * \file
 *
 * A PSP module to satisfy the "RAM" API on systems which
 * can access physical memory directly.
 */

#include "cfe_psp.h"
#include "cfe_psp_module.h"

CFE_PSP_MODULE_DECLARE_SIMPLE(ram_direct);

void ram_direct_Init(uint32 PspModuleId)
{
    /* Inform the user that this module is in use */
    printf("CFE_PSP: Using DIRECT memory mapped RAM implementation\n");
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
int32 CFE_PSP_MemRead8(cpuaddr MemoryAddress, uint8 *ByteValue)
{
    (*ByteValue) = *((uint8 *)MemoryAddress);

    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_MemWrite8(cpuaddr MemoryAddress, uint8 ByteValue)
{
    *((uint8 *)MemoryAddress) = ByteValue;
    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_MemRead16(cpuaddr MemoryAddress, uint16 *uint16Value)
{
    /* check 16 bit alignment  , check the 1st lsb */
    if (MemoryAddress & 0x00000001)
    {
        return CFE_PSP_ERROR_ADDRESS_MISALIGNED;
    }
    (*uint16Value) = *((uint16 *)MemoryAddress);
    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_MemWrite16(cpuaddr MemoryAddress, uint16 uint16Value)
{
    /* check 16 bit alignment  , check the 1st lsb */
    if (MemoryAddress & 0x00000001)
    {
        return CFE_PSP_ERROR_ADDRESS_MISALIGNED;
    }
    *((uint16 *)MemoryAddress) = uint16Value;
    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_MemRead32(cpuaddr MemoryAddress, uint32 *uint32Value)
{
    /* check 32 bit alignment  */
    if (MemoryAddress & 0x00000003)
    {
        return CFE_PSP_ERROR_ADDRESS_MISALIGNED;
    }
    (*uint32Value) = *((uint32 *)MemoryAddress);

    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_MemWrite32(cpuaddr MemoryAddress, uint32 uint32Value)
{
    /* check 32 bit alignment  */
    if (MemoryAddress & 0x00000003)
    {
        return CFE_PSP_ERROR_ADDRESS_MISALIGNED;
    }

    *((uint32 *)MemoryAddress) = uint32Value;

    return CFE_PSP_SUCCESS;
}
