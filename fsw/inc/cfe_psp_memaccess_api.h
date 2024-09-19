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
**  Author:  A. Cudmore
**
**  Purpose:  This file contains the cFE Platform Support Package(PSP)
**            prototypes.
**            The PSP routines serve as the "glue" between the RTOS and
**            the cFE Flight Software. The routines fill gaps that are not
**            really considered part of the OS Abstraction, but are required
**            for the cFE flight software implementation. It is possible that
**            some of these routines could migrate into the OS AL.
**
*/

#ifndef CFE_PSP_MEMACCESS_API_H
#define CFE_PSP_MEMACCESS_API_H

/******************************************************************************
 INCLUDE FILES
 ******************************************************************************/

#include "common_types.h"
#include "osapi.h"

#include "cfe_psp_error.h"

/*
** Memory API
*/
/*--------------------------------------------------------------------------------------*/
/**
 * @brief Read one byte of memory.
 *
 * @param[in]  MemoryAddress Address to be read
 * @param[out] ByteValue     The address content will be copied to the location pointed to by this argument
 *
 * @return Always returns CFE_PSP_SUCCESS (if implemented)
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_MemRead8(cpuaddr MemoryAddress, uint8 *ByteValue);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write one byte of memory.
 *
 * @param[out] MemoryAddress Address to be written to
 * @param[in]  ByteValue     The content pointed to by this argument will be copied to the address
 *
 * @return Always returns CFE_PSP_SUCCESS (if implemented)
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_MemWrite8(cpuaddr MemoryAddress, uint8 ByteValue);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Read 2 bytes of memory.
 *
 * @param[in]  MemoryAddress Address to be read
 * @param[out] uint16Value   The address content will be copied to the location pointed to by this argument
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_MemRead16(cpuaddr MemoryAddress, uint16 *uint16Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write 2 bytes of memory.
 *
 * @param[out] MemoryAddress Address to be written to
 * @param[in]  uint16Value   The content pointed to by this argument will be copied to the address
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_MemWrite16(cpuaddr MemoryAddress, uint16 uint16Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Read 4 bytes of memory.
 *
 * @param[in]  MemoryAddress Address to be read
 * @param[out] uint32Value   The address content will be copied to the location pointed to by this argument
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_MemRead32(cpuaddr MemoryAddress, uint32 *uint32Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write 4 bytes of memory.
 *
 * @param[out] MemoryAddress Address to be written to
 * @param[in]  uint32Value   The content pointed to by this argument will be copied to the address
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_MemWrite32(cpuaddr MemoryAddress, uint32 uint32Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Copy 'n' bytes from 'src' to 'dest'
 *
 * Copies 'n' bytes from memory address pointed to by 'src' to memory
 * address pointed to by 'dest'.
 *
 * @note For now we are using the standard C library call 'memcpy' but if we
 * find we need to make it more efficient then we'll implement it in assembly.
 *
 * @param[out] dest Pointer to the destination address to copy to
 * @param[in]  src  Pointer to the address to copy from
 * @param[in]  n    Number of bytes to copy
 *
 * @return Always returns CFE_PSP_SUCCESS
 */
int32 CFE_PSP_MemCpy(void *dest, const void *src, uint32 n);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Copy 'n' bytes of value 'value' to 'dest'
 *
 * Copies 'n' number of bytes of value 'value' to memory address pointed
 * to by 'dest'.
 *
 * @note For now we are using the standard C library call 'memset' but if we
 * find we need to make it more efficient then we'll implement it in assembly.
 *
 * @param[out] dest  Pointer to the destination address to copy to
 * @param[in]  value Value to set
 * @param[in]  n     Number of bytes to copy
 *
 * @return Always returns CFE_PSP_SUCCESS
 */
int32 CFE_PSP_MemSet(void *dest, uint8 value, uint32 n);

#endif
