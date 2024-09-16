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

#ifndef CFE_PSP_MEMRANGE_API_H
#define CFE_PSP_MEMRANGE_API_H

/******************************************************************************
 INCLUDE FILES
 ******************************************************************************/

#include "common_types.h"
#include "osapi.h"

#include "cfe_psp_error.h"

/******************************************************************************
 MACRO DEFINITIONS
 ******************************************************************************/

/*
** Define memory types
*/
#define CFE_PSP_MEM_RAM     1
#define CFE_PSP_MEM_EEPROM  2
#define CFE_PSP_MEM_ANY     3
#define CFE_PSP_MEM_INVALID 4

/*
** Define Memory Read/Write Attributes
*/
#define CFE_PSP_MEM_ATTR_WRITE     0x01
#define CFE_PSP_MEM_ATTR_READ      0x02
#define CFE_PSP_MEM_ATTR_READWRITE 0x03

/*
** Define the Memory Word Sizes
*/
#define CFE_PSP_MEM_SIZE_BYTE  0x01
#define CFE_PSP_MEM_SIZE_WORD  0x02
#define CFE_PSP_MEM_SIZE_DWORD 0x04

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the location and size of the ES Reset information area.
 *
 * This area is preserved during a processor reset and is used to store the ER
 * Log, System Log and reset-related variables
 *
 * @param[out] PtrToResetArea  Pointer to the variable that will store the location of the reset area
 * @param[out] SizeOfResetArea Pointer to the variable that will store the reset area size
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
int32 CFE_PSP_GetResetArea(cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the location and size of the memory used for the cFE user-reserved area.
 *
 * @param[out] PtrToUserArea  Pointer to the variable that will store the location of the user-reserved area
 * @param[out] SizeOfUserArea Pointer to the variable that will store the size of the user-reserved area
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea, uint32 *SizeOfUserArea);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the location and size of the memory used for the cFE volatile disk.
 *
 * @param[out] PtrToVolDisk  Pointer to the variable that will store the location of the cFE volatile disk
 * @param[out] SizeOfVolDisk Pointer to the variable that will store the size of the cFE volatile disk
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the location and size of the kernel memory.
 *
 * This function returns the start and end address of the kernel text segment.
 * It may not be implemented on all architectures.
 *
 * @param[out] PtrToKernelSegment  Pointer to the variable that will store the location of the kernel text segment
 * @param[out] SizeOfKernelSegment Pointer to the variable that will store the size of the kernel text segment
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 * or CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_GetKernelTextSegmentInfo(cpuaddr *PtrToKernelSegment, uint32 *SizeOfKernelSegment);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the location and size of the kernel memory.
 *
 * This function returns the start and end address of the CFE text segment. It
 * may not be implemented on all architectures.
 *
 * @param[out] PtrToCFESegment  Pointer to the variable that will store the location of the cFE text segment
 * @param[out] SizeOfCFESegment Pointer to the variable that will store the size of the cFE text segment
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment, uint32 *SizeOfCFESegment);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Validates the memory range and type using the global CFE_PSP_MemoryTable
 *
 * @param[in] Address    A 32-bit starting address of the memory range
 * @param[in] Size       A 32-bit size of the memory range (Address + Size = End Address)
 * @param[in] MemoryType The memory type to validate, including but not limited to:
 *                       CFE_PSP_MEM_RAM, CFE_PSP_MEM_EEPROM, or CFE_PSP_MEM_ANY
 *                       Any defined CFE_PSP_MEM_* enumeration can be specified
 *
 * @retval CFE_PSP_SUCCESS           Memory range and type information is valid and can be used.
 * @retval CFE_PSP_INVALID_MEM_ADDR  Starting address is not valid
 * @retval CFE_PSP_INVALID_MEM_TYPE  Memory type associated with the range does not match the passed-in type.
 * @retval CFE_PSP_INVALID_MEM_RANGE The Memory range associated with the address is not large enough to contain
 *                                   Address + Size.
 */
int32 CFE_PSP_MemValidateRange(cpuaddr Address, size_t Size, uint32 MemoryType);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the number of memory ranges in the CFE_PSP_MemoryTable
 *
 * @return Positive integer number of entries in the memory range table
 */
uint32 CFE_PSP_MemRanges(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Populates one of the records in the CFE_PSP_MemoryTable.
 *
 * @note Because the table is fixed size, the entries are set by using the
 * integer index. No validation is done with the address or size.
 *
 * @param[in] RangeNum   A 32-bit integer (starting with 0) specifying the MemoryTable entry.
 * @param[in] MemoryType The memory type to validate, including but not limited to:
 *                       CFE_PSP_MEM_RAM, CFE_PSP_MEM_EEPROM, or CFE_PSP_MEM_ANY
 *                       Any defined CFE_PSP_MEM_* enumeration can be specified
 * @param[in] StartAddr  A 32-bit starting address of the memory range
 * @param[in] Size       A 32-bit size of the memory range (Address + Size = End Address)
 * @param[in] WordSize   The minimum addressable size of the range:
 *                       (CFE_PSP_MEM_SIZE_BYTE, CFE_PSP_MEM_SIZE_WORD, CFE_PSP_MEM_SIZE_DWORD)
 * @param[in] Attributes The attributes of the Memory Range:
 *                       (CFE_PSP_MEM_ATTR_WRITE, CFE_PSP_MEM_ATTR_READ, CFE_PSP_MEM_ATTR_READWRITE)
 *
 * @retval CFE_PSP_SUCCESS              Memory range set successfully.
 * @retval CFE_PSP_INVALID_MEM_RANGE    The index into the table is invalid
 * @retval FE_PSP_INVALID_MEM_ADDR      Starting address is not valid
 * @retval CFE_PSP_INVALID_MEM_TYPE     Memory type associated with the range does not match the passed-in type.
 * @retval CFE_PSP_INVALID_MEM_WORDSIZE The WordSize parameter is not one of the predefined types.
 * @retval CFE_PSP_INVALID_MEM_ATTR     The Attributes parameter is not one of the predefined types.
 * @retval OP_INVALID_MEM_SIZE          The Memory range associated with the address is not large enough to contain
 *                                      Address + Size.
 */
int32 CFE_PSP_MemRangeSet(uint32 RangeNum, uint32 MemoryType, cpuaddr StartAddr, size_t Size, size_t WordSize,
                          uint32 Attributes);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Retrieves one of the records in the CFE_PSP_MemoryTable.
 *
 * @note Because the table is fixed size, the entries are accessed by using the integer index.
 *
 * @param[in]  RangeNum   A 32-bit integer (starting with 0) specifying the MemoryTable entry.
 * @param[out] MemoryType A pointer to the 32-bit integer where the Memory Type is stored.
 *                        Any defined CFE_PSP_MEM_* enumeration can be specified
 * @param[out] StartAddr  Pointer to the 32-bit integer where the 32-bit starting address of the memory range is stored.
 * @param[out] Size       A pointer to the 32-bit integer where the 32-bit size of the memory range is stored.
 * @param[out] WordSize   A pointer to the 32-bit integer where the minimum addressable size of the range:
 *                        (CFE_PSP_MEM_SIZE_BYTE, CFE_PSP_MEM_SIZE_WORD, CFE_PSP_MEM_SIZE_DWORD)
 * @param[out] Attributes The attributes of the Memory Range:
 *                        (CFE_PSP_MEM_ATTR_WRITE, CFE_PSP_MEM_ATTR_READ, CFE_PSP_MEM_ATTR_READWRITE)
 *
 * @retval CFE_PSP_SUCCESS           Memory range returned successfully.
 * @retval CFE_PSP_INVALID_POINTER   Parameter error
 * @retval CFE_PSP_INVALID_MEM_RANGE The index into the table is invalid
 */
int32 CFE_PSP_MemRangeGet(uint32 RangeNum, uint32 *MemoryType, cpuaddr *StartAddr, size_t *Size, size_t *WordSize,
                          uint32 *Attributes);

#endif
