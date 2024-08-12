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

/* PSP coverage stub replacement for moduleLib.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_moduleLib.h"

void UT_DefaultHandler_PCS_moduleFindByName(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* PCS_MODULE_ID PCS_moduleFindByName(const char *moduleName) */
    static PCS_MODULE UT_MODULE;
    PCS_MODULE_ID     retval;
    int32             Status;

    retval = NULL;

    UT_Stub_GetInt32StatusCode(Context, &Status);
    if (Status >= 0)
    {
        if (UT_Stub_CopyToLocal(FuncKey, &retval, sizeof(retval)) < sizeof(retval))
        {
            retval = &UT_MODULE;
        }
    }

    UT_Stub_SetReturnValue(FuncKey, retval);
}

void UT_DefaultHandler_PCS_moduleInfoGet(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* PCS_STATUS PCS_moduleInfoGet(PCS_MODULE_ID moduleId, PCS_MODULE_INFO *pModuleInfo) */
    PCS_MODULE_INFO *pModuleInfo = UT_Hook_GetArgValueByName(Context, "pModuleInfo", PCS_MODULE_INFO *);

    int32 Status;

    UT_Stub_GetInt32StatusCode(Context, &Status);

    if (Status >= 0 &&
        UT_Stub_CopyToLocal(UT_KEY(PCS_moduleInfoGet), pModuleInfo, sizeof(*pModuleInfo)) < sizeof(*pModuleInfo))
    {
        memset(pModuleInfo, 0, sizeof(*pModuleInfo));
    }
}
