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
 * Auto-Generated stub implementations for functions defined in PCS_moduleLib header
 */

#include "PCS_moduleLib.h"
#include "utgenstub.h"

void UT_DefaultHandler_PCS_moduleFindByName(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_moduleInfoGet(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_moduleFindByName()
 * ----------------------------------------------------
 */
PCS_MODULE_ID PCS_moduleFindByName(const char *moduleName)
{
    UT_GenStub_SetupReturnBuffer(PCS_moduleFindByName, PCS_MODULE_ID);

    UT_GenStub_AddParam(PCS_moduleFindByName, const char *, moduleName);

    UT_GenStub_Execute(PCS_moduleFindByName, Basic, UT_DefaultHandler_PCS_moduleFindByName);

    return UT_GenStub_GetReturnValue(PCS_moduleFindByName, PCS_MODULE_ID);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_moduleInfoGet()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_moduleInfoGet(PCS_MODULE_ID moduleId, PCS_MODULE_INFO *pModuleInfo)
{
    UT_GenStub_SetupReturnBuffer(PCS_moduleInfoGet, PCS_STATUS);

    UT_GenStub_AddParam(PCS_moduleInfoGet, PCS_MODULE_ID, moduleId);
    UT_GenStub_AddParam(PCS_moduleInfoGet, PCS_MODULE_INFO *, pModuleInfo);

    UT_GenStub_Execute(PCS_moduleInfoGet, Basic, UT_DefaultHandler_PCS_moduleInfoGet);

    return UT_GenStub_GetReturnValue(PCS_moduleInfoGet, PCS_STATUS);
}
