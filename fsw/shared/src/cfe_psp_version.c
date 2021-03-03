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

/**
 * \file cfe_psp_version.c
 *
 * Defines API that obtains the values of the various version identifiers
 */

#include <cfe_psp.h>
#include <cfe_psp_configdata.h>

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
    return GLOBAL_PSP_CONFIGDATA.PSP_VersionInfo.VersionString;
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
    return GLOBAL_PSP_CONFIGDATA.PSP_VersionInfo.VersionCodeName;
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
    VersionNumbers[0] = GLOBAL_PSP_CONFIGDATA.PSP_VersionInfo.MajorVersion;
    VersionNumbers[1] = GLOBAL_PSP_CONFIGDATA.PSP_VersionInfo.MinorVersion;
    VersionNumbers[2] = GLOBAL_PSP_CONFIGDATA.PSP_VersionInfo.Revision;
    VersionNumbers[3] = GLOBAL_PSP_CONFIGDATA.PSP_VersionInfo.MissionRev;
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
    return GLOBAL_PSP_CONFIGDATA.PSP_VersionInfo.BuildNumber;
}
