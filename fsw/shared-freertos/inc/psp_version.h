/*
**  GSC-18128-1, "Core Flight Executive Version 6.7"
**
**  Copyright (c) 2006-2019 United States Government as represented by
**  the Administrator of the National Aeronautics and Space Administration.
**  All Rights Reserved.
**
**  Licensed under the Apache License, Version 2.0 (the "License");
**  you may not use this file except in compliance with the License.
**  You may obtain a copy of the License at
**
**    http://www.apache.org/licenses/LICENSE-2.0
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
*/

/*! @file freertos/inc/psp_version.h
 *  @brief Purpose:
 *  @details Provide version identifiers for the cFE Platform Support Packages (PSP).
 *  See @ref cfsversions for version and build number and description
 */
#ifndef _psp_version_
#define _psp_version_

/*
 * Development Build Macro Definitions
 */
#define CFE_PSP_IMPL_BUILD_NUMBER   38
#define CFE_PSP_IMPL_BUILD_BASELINE "equuleus-rc1"
#define CFE_PSP_BUILD_CODENAME      "Equuleus" /**< @brief: Development: Code name for the current build */


/*
 * Version Macros, see \ref cfsversions for definitions.
 */
#define CFE_PSP_IMPL_MAJOR_VERSION 1  /*!< @brief Major version number */
#define CFE_PSP_IMPL_MINOR_VERSION 4  /*!< @brief Minor version number */
#define CFE_PSP_IMPL_REVISION      0  /*!< @brief Revision version number. Value of 0 indicates a development version.*/


/*!
 * @brief Mission revision.
 *
 * Reserved for mission use to denote patches/customizations as needed.
 * Values 1-254 are reserved for mission use to denote patches/customizations as needed. NOTE: Reserving 0 and 0xFF for
 * cFS open-source development use (pending resolution of nasa/cFS#440)
 */
#define CFE_PSP_IMPL_MISSION_REV 0xFF


/*
 * Tools to construct version string
 */
#define CFE_PSP_IMPL_STR_HELPER(x) #x /*!< @brief Helper function to concatenate strings from integer */
#define CFE_PSP_IMPL_STR(x) \
    CFE_PSP_IMPL_STR_HELPER(x) /*!< @brief Helper function to concatenate strings from integer */


/*! @brief DEVELOPMENT Build Version Number.
 *  @details Baseline git tag + Number of commits since baseline. @n
 *  See @ref cfsversions for format differences between development and release versions.
 */
#define CFE_PSP_IMPL_VERSION CFE_PSP_IMPL_BUILD_BASELINE "+dev" CFE_PSP_IMPL_STR(CFE_PSP_IMPL_BUILD_NUMBER)


#endif /* _psp_version_ */
