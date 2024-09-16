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

/*
 * NOTE: Normal behavior of this particular set of C library routines is important.
 *
 * Case in point - if code relies on something like memset() to clear memory, but that
 * memory is not cleared, then behavior of the code thereafter is undefined.  Thus, most
 * of the handlers here need to implement the real call by default.
 */

void UT_DefaultHandler_PCS_memset(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* void *PCS_memset(void *s, int c, size_t n) */
    void * s = UT_Hook_GetArgValueByName(Context, "s", void *);
    int    c = UT_Hook_GetArgValueByName(Context, "c", int);
    size_t n = UT_Hook_GetArgValueByName(Context, "n", size_t);

    void *Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = memset(s, c, n);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_memcpy(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* void *PCS_memcpy(void *dest, const void *src, size_t n) */
    void *      dest = UT_Hook_GetArgValueByName(Context, "dest", void *);
    const void *src  = UT_Hook_GetArgValueByName(Context, "src", const void *);
    size_t      n    = UT_Hook_GetArgValueByName(Context, "n", size_t);

    void *Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = memcpy(dest, src, n);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_memchr(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* void * PCS_memchr(const void *s, int c, size_t n) */
    void * s = UT_Hook_GetArgValueByName(Context, "s", void *);
    int    c = UT_Hook_GetArgValueByName(Context, "c", int);
    size_t n = UT_Hook_GetArgValueByName(Context, "n", size_t);

    void *Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = memchr(s, c, n);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_memcmp(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int PCS_memcmp(void *dest, const void *src, size_t n) */
    void *      dest = UT_Hook_GetArgValueByName(Context, "dest", void *);
    const void *src  = UT_Hook_GetArgValueByName(Context, "src", const void *);
    size_t      n    = UT_Hook_GetArgValueByName(Context, "n", size_t);

    int Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = memcmp(dest, src, n);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_strchr(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* char *PCS_strchr(const char *s, int c) */
    const char *s = UT_Hook_GetArgValueByName(Context, "s", const char *);
    int         c = UT_Hook_GetArgValueByName(Context, "c", int);

    char *Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = strchr(s, c);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_strrchr(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* char *PCS_strrchr(const char *s, int c) */
    const char *s = UT_Hook_GetArgValueByName(Context, "s", const char *);
    int         c = UT_Hook_GetArgValueByName(Context, "c", int);

    char *Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = strrchr(s, c);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_strlen(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* size_t PCS_strlen(const char *s) */
    const char *s = UT_Hook_GetArgValueByName(Context, "s", const char *);

    size_t Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = strlen(s);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_strcat(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* char *PCS_strcat(char *dest, const char *src) */
    void *      dest = UT_Hook_GetArgValueByName(Context, "dest", void *);
    const void *src  = UT_Hook_GetArgValueByName(Context, "src", const void *);

    char *Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = strcat(dest, src);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_strncat(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* char *PCS_strncat(char *dest, const char *src, size_t size) */
    void *      dest = UT_Hook_GetArgValueByName(Context, "dest", void *);
    const void *src  = UT_Hook_GetArgValueByName(Context, "src", const void *);
    size_t      size = UT_Hook_GetArgValueByName(Context, "size", size_t);

    char *Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = strncat(dest, src, size);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_strncmp(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int    PCS_strncmp(const char *s1, const char *s2, size_t n) */
    const char *s1 = UT_Hook_GetArgValueByName(Context, "s1", const char *);
    const char *s2 = UT_Hook_GetArgValueByName(Context, "s2", const char *);
    size_t      n  = UT_Hook_GetArgValueByName(Context, "n", size_t);

    int Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = strncmp(s1, s2, n);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_strcmp(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int PCS_strcmp(const char *s1, const char *s2) */
    const char *s1 = UT_Hook_GetArgValueByName(Context, "s1", const char *);
    const char *s2 = UT_Hook_GetArgValueByName(Context, "s2", const char *);

    int Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = strcmp(s1, s2);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_strcpy(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* char *PCS_strcpy(char *dst, const char *src) */
    char *      dst = UT_Hook_GetArgValueByName(Context, "dst", char *);
    const char *src = UT_Hook_GetArgValueByName(Context, "src", const char *);

    char *Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = strcpy(dst, src);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_strncpy(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* char *PCS_strncpy(char *dst, const char *src, size_t size) */
    char *      dst  = UT_Hook_GetArgValueByName(Context, "dst", char *);
    const char *src  = UT_Hook_GetArgValueByName(Context, "src", const char *);
    size_t      size = UT_Hook_GetArgValueByName(Context, "size", size_t);

    char *Result;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform the real operation */
        Result = strncpy(dst, src, size);
        UT_Stub_SetReturnValue(FuncKey, Result);
    }
}

void UT_DefaultHandler_PCS_strerror(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* char *PCS_strerror(int errnum) */
    int errnum = UT_Hook_GetArgValueByName(Context, "errnum", int);

    static char str[16];
    char *      ret = str;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        /* Perform a substitute operation */
        snprintf(str, sizeof(str), "UT_ERR_%d", errnum);
        UT_Stub_SetReturnValue(FuncKey, ret);
    }
}
