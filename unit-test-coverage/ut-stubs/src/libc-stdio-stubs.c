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

int PCS_fclose(PCS_FILE *stream)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_fclose);

    return Status;
}

char *PCS_fgets(char *s, int n, PCS_FILE *stream)
{
    int32  Status;
    uint32 CopySize;

    Status = UT_DEFAULT_IMPL_RC(PCS_fgets, PCS_STDIO_MAX_SIZE);

    if (Status > 0)
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

        if (CopySize != 0)
        {
            Status = CopySize;
        }
        else if (Status <= n)
        {
            memset(s, 'x', Status);
        }
        else if (UT_GetStubCount(UT_KEY(PCS_fgets) < 4))
        {
            memset(s, 'x', n);
            Status = n;
        }
        else
        {
            Status = 0;
        }
    }

    if (Status <= 0)
    {
        return NULL;
    }

    return s;
}

PCS_FILE *PCS_fopen(const char *filename, const char *modes)
{
    int32           Status;
    PCS_FILE *      retval;
    static PCS_FILE FOPEN_FP = {0};

    Status = UT_DEFAULT_IMPL(PCS_fopen);

    if (Status == 0)
    {
        retval = &FOPEN_FP;
    }
    else
    {
        retval = NULL;
    }

    return retval;
}

int PCS_fputs(const char *s, PCS_FILE *stream)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_fputs);

    return Status;
}

int PCS_putchar(int c)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_putchar);

    return Status;
}

int PCS_remove(const char *filename)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_remove);

    return Status;
}

int PCS_rename(const char *old, const char *nw)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_rename);

    return Status;
}

int PCS_snprintf(char *s, size_t maxlen, const char *format, ...)
{
    int32   Status;
    int     actual = 0;
    va_list ap;

    Status = UT_DEFAULT_IMPL(PCS_snprintf);

    /* need to actually _do_ the snprintf */
    if (Status >= 0)
    {
        va_start(ap, format);
        actual = vsnprintf(s, maxlen, format, ap);
        va_end(ap);
    }

    if (Status != 0)
    {
        actual = Status;
    }

    return actual;
}

int PCS_vsnprintf(char *s, size_t maxlen, const char *format, PCS_va_list arg)
{
    int32 Status;
    int   actual = 0;

    Status = UT_DEFAULT_IMPL(PCS_vsnprintf);

    /* need to actually _do_ something here -
     * cannot do the real vsnprintf because we lost the args. */
    if (Status >= 0)
    {
        actual = snprintf(s, maxlen, "%s", format);
    }

    if (Status != 0)
    {
        actual = Status;
    }

    return actual;
}

int PCS_printf(const char *format, ...)
{
    return UT_DEFAULT_IMPL(PCS_printf);
}

static PCS_FILE LOCAL_FP[3] = {{10}, {11}, {12}};

PCS_FILE *PCS_stdin  = &LOCAL_FP[0];
PCS_FILE *PCS_stdout = &LOCAL_FP[1];
PCS_FILE *PCS_stderr = &LOCAL_FP[2];
