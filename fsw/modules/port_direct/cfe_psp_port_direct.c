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
 * A PSP module to satisfy the "PORT" API on systems which
 * can access I/O ports directly via memory mapped addresses.
 */

#include "cfe_psp.h"
#include "cfe_psp_module.h"

CFE_PSP_MODULE_DECLARE_SIMPLE(port_direct);

void port_direct_Init(uint32 PspModuleId)
{
    /* Inform the user that this module is in use */
    printf("CFE_PSP: Using DIRECT memory mapped PORT implementation\n");
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
int32 CFE_PSP_PortRead8(cpuaddr PortAddress, uint8 *ByteValue)
{
    (*ByteValue) = (uint8) * ((uint8 *)PortAddress);

    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_PortWrite8(cpuaddr PortAddress, uint8 ByteValue)
{
    *((uint8 *)PortAddress) = ByteValue;
    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_PortRead16(cpuaddr PortAddress, uint16 *uint16Value)
{
    /* check 16 bit alignment  , check the 1st lsb */
    if (PortAddress & 0x00000001)
    {
        return CFE_PSP_ERROR_ADDRESS_MISALIGNED;
    }
    (*uint16Value) = *((uint16 *)PortAddress);
    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_PortWrite16(cpuaddr PortAddress, uint16 uint16Value)
{
    /* check 16 bit alignment  , check the 1st lsb */
    if (PortAddress & 0x00000001)
    {
        return CFE_PSP_ERROR_ADDRESS_MISALIGNED;
    }
    *((uint16 *)PortAddress) = uint16Value;
    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_PortRead32(cpuaddr PortAddress, uint32 *uint32Value)
{
    /* check 32 bit alignment  */
    if (PortAddress & 0x00000003)
    {
        return CFE_PSP_ERROR_ADDRESS_MISALIGNED;
    }
    (*uint32Value) = *((uint32 *)PortAddress);
    return CFE_PSP_SUCCESS;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_PortWrite32(cpuaddr PortAddress, uint32 uint32Value)
{
    /* check 32 bit alignment  */
    if (PortAddress & 0x00000003)
    {
        return CFE_PSP_ERROR_ADDRESS_MISALIGNED;
    }
    *((uint32 *)PortAddress) = uint32Value;
    return CFE_PSP_SUCCESS;
}
