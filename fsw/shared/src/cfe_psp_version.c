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

/**
 * \file
 *
 * Defines API that obtains the values of the various version identifiers
 */

#include "cfe_psp.h"
#include "psp_version.h"

/*----------------------------------------------------------------
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
 *  Purpose: Implemented per public OSAL API
 *           See description in API and header file for detail
 *
 *-----------------------------------------------------------------*/
uint32 CFE_PSP_GetBuildNumber(void)
{
    return CFE_PSP_IMPL_BUILD_NUMBER;
}
