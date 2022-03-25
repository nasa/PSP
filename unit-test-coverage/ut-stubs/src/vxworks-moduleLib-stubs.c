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

PCS_MODULE_ID PCS_moduleFindByName(const char *moduleName)
{
    PCS_MODULE_ID retval;
    int32         Status;

    retval = NULL;
    Status = UT_DEFAULT_IMPL(PCS_moduleFindByName);
    if (Status == 0)
    {
        UT_Stub_CopyToLocal(UT_KEY(PCS_moduleFindByName), &retval, sizeof(retval));
    }

    return retval;
}

PCS_STATUS PCS_moduleInfoGet(PCS_MODULE_ID moduleId, PCS_MODULE_INFO *pModuleInfo)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_moduleInfoGet);

    if (Status == 0 &&
        UT_Stub_CopyToLocal(UT_KEY(PCS_moduleInfoGet), pModuleInfo, sizeof(*pModuleInfo)) < sizeof(*pModuleInfo))
    {
        memset(pModuleInfo, 0, sizeof(*pModuleInfo));
    }

    return Status;
}
