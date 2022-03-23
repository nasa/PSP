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

/* PSP coverage stub replacement for string.h */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utstubs.h"

#include "PCS_string.h"

void *PCS_memset(void *s, int c, size_t n)
{
    int32 Status;
    void *Result;

    Status = UT_DEFAULT_IMPL(PCS_memset);

    if (Status == 0)
    {
        Result = memset(s, c, n);
    }
    else
    {
        Result = NULL;
    }

    return Result;
}

void *PCS_memcpy(void *dest, const void *src, size_t n)
{
    int32 Status;
    void *Result;

    Status = UT_DEFAULT_IMPL(PCS_memcpy);

    if (Status == 0)
    {
        Result = memcpy(dest, src, n);
    }
    else
    {
        Result = NULL;
    }

    return Result;
}

char *PCS_strchr(const char *s, int c)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_strchr);

    if (Status == 0)
    {
        /* "nominal" response */
        return strchr(s, c);
    }
    if (Status < 0)
    {
        return (char *)0;
    }

    return (char *)&s[Status - 1];
}

char *PCS_strrchr(const char *s, int c)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_strrchr);

    if (Status == 0)
    {
        /* "nominal" response */
        return strrchr(s, c);
    }
    if (Status < 0)
    {
        return (char *)0;
    }

    return (char *)&s[Status - 1];
}

size_t PCS_strlen(const char *s)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL_RC(PCS_strlen, strlen(s));

    return Status;
}

char *PCS_strcat(char *dest, const char *src)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_strcat);

    if (Status == 0)
    {
        /* "nominal" response */
        return strcat(dest, src);
    }

    return (char *)0;
}

char *PCS_strncat(char *dest, const char *src, size_t size)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_strncat);

    if (Status == 0)
    {
        /* "nominal" response */
        return strncat(dest, src, size);
    }

    return (char *)0;
}

int PCS_strncmp(const char *s1, const char *s2, size_t size)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL_RC(PCS_strncmp, strncmp(s1, s2, size));

    return Status;
}

int PCS_strcmp(const char *s1, const char *s2)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL_RC(PCS_strcmp, strcmp(s1, s2));

    return Status;
}

char *PCS_strcpy(char *dst, const char *src)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_strcpy);

    if (Status == 0)
    {
        /* "nominal" response */
        return strcpy(dst, src);
    }

    return (char *)0;
}

char *PCS_strncpy(char *dst, const char *src, size_t size)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_strncpy);

    if (Status == 0)
    {
        /* "nominal" response */
        return strncpy(dst, src, size);
    }

    return (char *)0;
}

char *PCS_strerror(int errnum)
{
    static char str[16];
    int32       Status;

    Status = UT_DEFAULT_IMPL(PCS_strerror);

    if (Status != 0)
    {
        return NULL;
    }

    /* "nominal" response */
    snprintf(str, sizeof(str), "UT_ERR_%d", errnum);
    return str;
}
