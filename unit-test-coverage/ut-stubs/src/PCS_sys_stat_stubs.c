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
 * Auto-Generated stub implementations for functions defined in PCS_sys_stat header
 */

#include "PCS_sys_stat.h"
#include "utgenstub.h"

void UT_DefaultHandler_PCS_stat(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_statfs(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_stat()
 * ----------------------------------------------------
 */
int PCS_stat(const char *path, struct PCS_stat *buf)
{
    UT_GenStub_SetupReturnBuffer(PCS_stat, int);

    UT_GenStub_AddParam(PCS_stat, const char *, path);
    UT_GenStub_AddParam(PCS_stat, struct PCS_stat *, buf);

    UT_GenStub_Execute(PCS_stat, Basic, UT_DefaultHandler_PCS_stat);

    return UT_GenStub_GetReturnValue(PCS_stat, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_statfs()
 * ----------------------------------------------------
 */
int PCS_statfs(const char *path, struct PCS_statfs *buf)
{
    UT_GenStub_SetupReturnBuffer(PCS_statfs, int);

    UT_GenStub_AddParam(PCS_statfs, const char *, path);
    UT_GenStub_AddParam(PCS_statfs, struct PCS_statfs *, buf);

    UT_GenStub_Execute(PCS_statfs, Basic, UT_DefaultHandler_PCS_statfs);

    return UT_GenStub_GetReturnValue(PCS_statfs, int);
}
