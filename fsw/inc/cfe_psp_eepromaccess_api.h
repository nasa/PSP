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

#ifndef CFE_PSP_EEPROMACCESS_API_H
#define CFE_PSP_EEPROMACCESS_API_H

/******************************************************************************
 INCLUDE FILES
 ******************************************************************************/

#include "common_types.h"
#include "osapi.h"

#include "cfe_psp_error.h"

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write one byte (ByteValue) to EEPROM address MemoryAddress
 *
 * @param[out] MemoryAddress Memory address to write to
 * @param[in]  ByteValue     Value to write to memory
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_TIMEOUT write operation did not go through after a specific timeout.
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromWrite8(cpuaddr MemoryAddress, uint8 ByteValue);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write two bytes (uint16Value) to EEPROM address MemoryAddress
 *
 * @param[out] MemoryAddress Memory address to write to
 * @param[in]  uint16Value   Value to write to memory
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_TIMEOUT write operation did not go through after a specific timeout.
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromWrite16(cpuaddr MemoryAddress, uint16 uint16Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write four bytes (uint32Value) to EEPROM address MemoryAddress
 *
 * @param[out] MemoryAddress Memory address to write to
 * @param[in]  uint32Value   Value to write to memory
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_TIMEOUT write operation did not go through after a specific timeout.
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromWrite32(cpuaddr MemoryAddress, uint32 uint32Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Enable the EEPROM for write operation
 *
 * @param[in] Bank The bank of EEPROM to enable
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromWriteEnable(uint32 Bank);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Disable the EEPROM from write operation
 *
 * @param[in] Bank The bank of EEPROM to disable
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromWriteDisable(uint32 Bank);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Power up the EEPROM
 *
 * @param[in] Bank The bank of EEPROM to power up
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromPowerUp(uint32 Bank);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Power down the EEPROM
 *
 * @param[in] Bank The bank of EEPROM to power down
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromPowerDown(uint32 Bank);

#endif
