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

/*! @file
 *  @brief Purpose:
 *  @details Provide version identifiers for the cFE Platform Support Packages (PSP).
 *  See @ref cfsversions for version and build number and description
 */
#ifndef PSP_VERSION_H
#define PSP_VERSION_H

/*
 * Development Build Macro Definitions
 */
#define CFE_PSP_IMPL_BUILD_NUMBER   14
#define CFE_PSP_IMPL_BUILD_BASELINE "v1.6.0-rc1"

/*
 * Version Macro Definitions
 */
#define CFE_PSP_IMPL_MAJOR_VERSION 1 /*!< @brief ONLY APPLY for OFFICIAL releases. Major version number. */
#define CFE_PSP_IMPL_MINOR_VERSION 4 /*!< @brief ONLY APPLY for OFFICIAL releases. Minor version number. */
#define CFE_PSP_IMPL_REVISION      0 /*!< @brief ONLY APPLY for OFFICIAL releases. Revision number. */

/*!
 * @brief Mission revision.
 *
 * Set to 0 on OFFICIAL releases, and set to 255 (0xFF) on development versions.
 * Values 1-254 are reserved for mission use to denote patches/customizations as needed.
 */
#define CFE_PSP_IMPL_MISSION_REV 0xFF

#define CFE_PSP_IMPL_CODENAME "Draco"

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

/*! @brief DEVELOPMENT Build Version String.
 *  @details Reports the current development build's baseline, number, and name. Also includes a note about the latest
 * official version. @n See @ref cfsversions for format differences between development and release versions.
 */
#define CFE_PSP_IMPL_VERSION_STRING                \
    " PSP DEVELOPMENT BUILD " CFE_PSP_IMPL_VERSION \
    ", Last Official Release: psp v1.4.0" /* For full support please use this version */

#endif
