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

/* PSP coverage stub replacement for userReservedMem.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_sys_stat.h"

void UT_DefaultHandler_PCS_stat(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int PCS_stat(const char *file, struct PCS_stat *buf) */
    struct PCS_stat *buf = UT_Hook_GetArgValueByName(Context, "buf", struct PCS_stat *);
    int32            Status;

    UT_Stub_GetInt32StatusCode(Context, &Status);

    if (Status == 0 && UT_Stub_CopyToLocal(UT_KEY(PCS_stat), buf, sizeof(*buf)) < sizeof(*buf))
    {
        memset(buf, 0, sizeof(*buf));
    }
}

void UT_DefaultHandler_PCS_statfs(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int PCS_statfs(const char *path, struct PCS_statfs *buf) */
    struct PCS_statfs *buf = UT_Hook_GetArgValueByName(Context, "buf", struct PCS_statfs *);
    int32              iStatus;

    UT_Stub_GetInt32StatusCode(Context, &iStatus);

    if (iStatus == 0)
    {
        UT_Stub_CopyToLocal(UT_KEY(PCS_statfs), (struct PCS_statfs *)buf, sizeof(*buf));
    }
}
