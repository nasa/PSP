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
