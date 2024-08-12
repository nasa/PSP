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
 * @file
 *
 * Auto-Generated stub implementations for functions defined in cfe_psp_version_api header
 */

#include "cfe_psp_version_api.h"
#include "utgenstub.h"

void UT_DefaultHandler_CFE_PSP_GetVersionCodeName(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_GetVersionString(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_GetBuildNumber()
 * ----------------------------------------------------
 */
uint32 CFE_PSP_GetBuildNumber(void)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_GetBuildNumber, uint32);

    UT_GenStub_Execute(CFE_PSP_GetBuildNumber, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_GetBuildNumber, uint32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_GetVersionCodeName()
 * ----------------------------------------------------
 */
const char *CFE_PSP_GetVersionCodeName(void)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_GetVersionCodeName, const char *);

    UT_GenStub_Execute(CFE_PSP_GetVersionCodeName, Basic, UT_DefaultHandler_CFE_PSP_GetVersionCodeName);

    return UT_GenStub_GetReturnValue(CFE_PSP_GetVersionCodeName, const char *);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_GetVersionNumber()
 * ----------------------------------------------------
 */
void CFE_PSP_GetVersionNumber(uint8 VersionNumbers[4])
{

    UT_GenStub_Execute(CFE_PSP_GetVersionNumber, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_GetVersionString()
 * ----------------------------------------------------
 */
const char *CFE_PSP_GetVersionString(void)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_GetVersionString, const char *);

    UT_GenStub_Execute(CFE_PSP_GetVersionString, Basic, UT_DefaultHandler_CFE_PSP_GetVersionString);

    return UT_GenStub_GetReturnValue(CFE_PSP_GetVersionString, const char *);
}
