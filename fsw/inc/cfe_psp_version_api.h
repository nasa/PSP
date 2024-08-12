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

#ifndef CFE_PSP_VERSION_API_H
#define CFE_PSP_VERSION_API_H

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
 * @brief Obtain the PSP version/baseline identifier string
 *
 * This retrieves the PSP version identifier string without extra info
 *
 * @return Version string. This is a fixed string and cannot be NULL.
 */
const char *CFE_PSP_GetVersionString(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Obtain the version code name
 *
 * This retrieves the PSP code name. This is a compatibility indicator for the
 * overall NASA cFS ecosystem. All modular components which are intended to
 * interoperate should report the same code name.
 *
 * @return Code name. This is a fixed string and cannot be NULL.
 */
const char *CFE_PSP_GetVersionCodeName(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Retrieves the numeric PSP version identifier as an array of uint8 values
 *
 * The array of numeric values is in order of precedence:
 *  [0] = Major Number
 *  [1] = Minor Number
 *  [2] = Revision Number
 *  [3] = Mission Revision
 *
 * The "Mission Revision" (last output) also indicates whether this is an
 * official release, a patched release, or a development version.
 *  0 indicates an official release
 *  1-254 local patch level (reserved for mission use)
 *  255 indicates a development build
 *
 * @param[out] VersionNumbers A fixed-size array to be filled with the version numbers
 */
void CFE_PSP_GetVersionNumber(uint8 VersionNumbers[4]);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Obtain the PSP library numeric build number
 *
 * The build number is a monotonically increasing number that (coarsely)
 * reflects the number of commits/changes that have been merged since the epoch
 * release. During development cycles this number should increase after each
 * subsequent merge/modification.
 *
 * Like other version information, this is a fixed number assigned at compile
 * time.
 *
 * @return The OSAL library build number
 */
uint32 CFE_PSP_GetBuildNumber(void);

#endif
