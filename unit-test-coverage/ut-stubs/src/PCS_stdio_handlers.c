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

/* PSP coverage stub replacement for stdio.h */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utstubs.h"

#include "PCS_stdio.h"

struct PCS_FILE
{
    int f;
};

#define PCS_STDIO_MAX_SIZE 0x01000000

void UT_DefaultHandler_PCS_fgets(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* char *PCS_fgets(char *s, int n, PCS_FILE *stream) */
    char *s = UT_Hook_GetArgValueByName(Context, "s", char *);
    int   n = UT_Hook_GetArgValueByName(Context, "n", int);

    int32  Status;
    uint32 CopySize;
    void * DataBufferPtr;

    Status = 0;
    UT_GetDataBuffer(FuncKey, &DataBufferPtr, NULL, NULL);
    UT_Stub_GetInt32StatusCode(Context, &Status);

    if (DataBufferPtr != NULL)
    {
        if (Status > n)
        {
            CopySize = n;
        }
        else
        {
            CopySize = Status;
        }

        CopySize = UT_Stub_CopyToLocal(UT_KEY(PCS_fgets), s, CopySize);
    }
    else
    {
        CopySize = 0;
    }

    if (n < Status)
    {
        Status = n;
    }

    if (UT_GetStubCount(UT_KEY(PCS_fgets) < 4) && Status > 0 && CopySize < Status)
    {
        memset(&s[CopySize], 'x', Status - CopySize);
        CopySize = Status;
    }

    if (CopySize <= 0)
    {
        s = NULL;
    }
    else
    {
        s[CopySize - 1] = 0;
    }

    UT_Stub_SetReturnValue(FuncKey, s);
}

void UT_DefaultHandler_PCS_fopen(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* PCS_FILE *PCS_fopen(const char *filename, const char *modes) */
    PCS_FILE *      retval;
    static PCS_FILE FOPEN_FP = {0};

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        retval = &FOPEN_FP;
        UT_Stub_SetReturnValue(FuncKey, retval);
    }
}

void UT_DefaultHandler_PCS_snprintf(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context,
                                    va_list ArgList)
{
    /* int PCS_snprintf(char *s, size_t maxlen, const char *format, ...) */
    char *      s      = UT_Hook_GetArgValueByName(Context, "s", char *);
    size_t      maxlen = UT_Hook_GetArgValueByName(Context, "maxlen", size_t);
    const char *format = UT_Hook_GetArgValueByName(Context, "format", const char *);
    int32       status;

    int retval;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        /* need to actually _do_ the snprintf */
        retval = vsnprintf(s, maxlen, format, ArgList);

        /* It is assumed that zero implies normal snprintf behavior,
         * anything else is an intended return value */
        if (status == 0)
        {
            UT_Stub_SetReturnValue(FuncKey, retval);
        }
    }
}

void UT_DefaultHandler_PCS_vsnprintf(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int PCS_vsnprintf(char *s, size_t maxlen, const char *format, PCS_va_list arg) */
    char *      s      = UT_Hook_GetArgValueByName(Context, "s", char *);
    size_t      maxlen = UT_Hook_GetArgValueByName(Context, "maxlen", size_t);
    const char *format = UT_Hook_GetArgValueByName(Context, "format", const char *);

    int retval = 0;

    /* need to actually _do_ something here -
     * cannot do the real vsnprintf because we lost the args. */
    retval = snprintf(s, maxlen, "%s", format);
    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        UT_Stub_SetReturnValue(FuncKey, retval);
    }
}

static PCS_FILE LOCAL_FP[3] = {{10}, {11}, {12}};

PCS_FILE *PCS_stdin  = &LOCAL_FP[0];
PCS_FILE *PCS_stdout = &LOCAL_FP[1];
PCS_FILE *PCS_stderr = &LOCAL_FP[2];
