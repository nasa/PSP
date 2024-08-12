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

#ifndef CFE_PSP_CDS_API_H
#define CFE_PSP_CDS_API_H

/******************************************************************************
 INCLUDE FILES
 ******************************************************************************/

#include "common_types.h"
#include "osapi.h"

#include "cfe_psp_error.h"

/******************************************************************************
 FUNCTION PROTOTYPES
 ******************************************************************************/

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Fetches the size of the OS Critical Data Store area.
 *
 * @param[out] SizeOfCDS Pointer to the variable that will store the size of the CDS
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Writes to the CDS Block.
 *
 * @param[in] PtrToDataToWrite Pointer to the data that will be written to the CDS
 * @param[in] CDSOffset        CDS offset
 * @param[in] NumBytes         Number of bytes to write
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
int32 CFE_PSP_WriteToCDS(const void *PtrToDataToWrite, uint32 CDSOffset, uint32 NumBytes);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Reads from the CDS Block
 *
 * @param[out] PtrToDataFromRead Pointer to the location that will store the data to be read from the CDS
 * @param[in]  CDSOffset         CDS offset
 * @param[in]  NumBytes          Number of bytes to read
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
int32 CFE_PSP_ReadFromCDS(void *PtrToDataFromRead, uint32 CDSOffset, uint32 NumBytes);

#endif
