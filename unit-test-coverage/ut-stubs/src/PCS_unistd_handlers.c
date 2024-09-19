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

/************************************************************************
 * Note that this file has been cloned-n-owned from its open-source github
 * repository for Gateway as of September 2023. Therefore, it is subject to
 * NASA Export Control restrictions, as stated below.
 ************************************************************************/

/************************************************************************/
/** \export_control EAR ECCN 9E515.a and/or 9E515.f (HALO)
 *
 * Export Administration Regulations (EAR) Notice
 *
 * This document contains information which falls under the purview of the
 * Export Administration Regulations (EAR), 15 CFR §730-774 and is export
 * controlled. It may be used only to fulfill responsibilities of the Parties
 * of, or a Cooperating Agency of a NASA Gateway Program Partner (CSA, ESA,
 * JAXA, MBRSC) and their contractors in furtherance of the Gateway MOUs
 * with ESA, CSA, and Japan and IA with MBRSC. Any use, re-transfer, or
 * disclosure to any party for any purpose other than the designated use of
 * fulfilling the responsibilities of the Gateway MOUs and IA requires prior
 * U.S. Government authorization.
 *************************************************************************/

/* PSP coverage stub replacement for unistd.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_unistd.h"

#define PCS_MAX_RDWR_SIZE 0x01000000 /* 16MB */

void UT_DefaultHandler_PCS_gethostname(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int PCS_gethostname(char *name, size_t len) */
    char * name = UT_Hook_GetArgValueByName(Context, "name", char *);
    size_t len  = UT_Hook_GetArgValueByName(Context, "len", size_t);
    int32  Status;

    UT_Stub_GetInt32StatusCode(Context, &Status);

    if (Status == 0 && len > 0)
    {
        strncpy(name, "ut", len - 1);
        name[len - 1] = 0;
    }
}

void UT_DefaultHandler_PCS_read(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* PCS_ssize_t PCS_read(int fd, void *buf, size_t nbytes) */
    void *      buf    = UT_Hook_GetArgValueByName(Context, "buf", void *);
    size_t      nbytes = UT_Hook_GetArgValueByName(Context, "nbytes", size_t);
    int32       Status;
    size_t      CopySize;
    PCS_ssize_t retval;

    if (!UT_Stub_GetInt32StatusCode(Context, &Status))
    {
        Status = PCS_MAX_RDWR_SIZE;
    }

    if (Status > 0)
    {
        if (Status > nbytes)
        {
            CopySize = nbytes;
        }
        else
        {
            CopySize = Status;
        }

        CopySize = UT_Stub_CopyToLocal(FuncKey, buf, CopySize);

        if (CopySize != 0)
        {
            retval = CopySize;
        }
        else if (Status <= nbytes)
        {
            memset(buf, 'r', Status);
            retval = Status;
        }
        else if (UT_GetStubCount(FuncKey < 4))
        {
            memset(buf, 'r', nbytes);
            retval = nbytes;
        }
        else
        {
            retval = 0;
        }

        UT_Stub_SetReturnValue(FuncKey, retval);
    }
}

void UT_DefaultHandler_PCS_write(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* PCS_ssize_t PCS_write(int fd, const void *buf, size_t nbytes) */
    const void *buf    = UT_Hook_GetArgValueByName(Context, "buf", const void *);
    size_t      nbytes = UT_Hook_GetArgValueByName(Context, "nbytes", size_t);
    int32       Status;
    size_t      CopySize;
    PCS_ssize_t retval;

    if (!UT_Stub_GetInt32StatusCode(Context, &Status))
    {
        Status = PCS_MAX_RDWR_SIZE;
    }

    if (Status > 0)
    {
        if (Status > nbytes)
        {
            CopySize = nbytes;
        }
        else
        {
            CopySize = Status;
        }

        CopySize = UT_Stub_CopyFromLocal(FuncKey, buf, CopySize);

        if (CopySize != 0)
        {
            retval = CopySize;
        }
        else if (Status > nbytes)
        {
            retval = nbytes;
        }
        else
        {
            retval = Status;
        }

        UT_Stub_SetReturnValue(FuncKey, retval);
    }
}
