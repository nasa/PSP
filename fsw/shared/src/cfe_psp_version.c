/**
 * \file
 *
 * Defines API that obtains the values of the various version identifiers
 */

#include "cfe_psp.h"
#include "psp_version.h"

/*----------------------------------------------------------------
 *
 * Function: CFE_PSP_GetVersionString
 *
 *  Purpose: Implemented per public OSAL API
 *           See description in API and header file for detail
 *
 *-----------------------------------------------------------------*/
const char *CFE_PSP_GetVersionString(void)
{
    return CFE_PSP_IMPL_VERSION;
}

/*----------------------------------------------------------------
 *
 * Function: CFE_PSP_GetVersionCodeName
 *
 *  Purpose: Implemented per public OSAL API
 *           See description in API and header file for detail
 *
 *-----------------------------------------------------------------*/
const char *CFE_PSP_GetVersionCodeName(void)
{
    return CFE_PSP_IMPL_CODENAME;
}

/*----------------------------------------------------------------
 *
 * Function: CFE_PSP_GetVersionNumber
 *
 *  Purpose: Implemented per public OSAL API
 *           See description in API and header file for detail
 *
 *-----------------------------------------------------------------*/
void CFE_PSP_GetVersionNumber(uint8 VersionNumbers[4])
{
    VersionNumbers[0] = CFE_PSP_IMPL_MAJOR_VERSION;
    VersionNumbers[1] = CFE_PSP_IMPL_MINOR_VERSION;
    VersionNumbers[2] = CFE_PSP_IMPL_REVISION;
    VersionNumbers[3] = CFE_PSP_IMPL_MISSION_REV;
}

/*----------------------------------------------------------------
 *
 * Function: CFE_PSP_GetBuildNumber
 *
 *  Purpose: Implemented per public OSAL API
 *           See description in API and header file for detail
 *
 *-----------------------------------------------------------------*/
uint32 CFE_PSP_GetBuildNumber(void)
{
    return CFE_PSP_IMPL_BUILD_NUMBER;
}
