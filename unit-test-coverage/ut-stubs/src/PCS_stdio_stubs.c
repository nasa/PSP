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
 * Auto-Generated stub implementations for functions defined in PCS_stdio header
 */

#include <stdarg.h>

#include "PCS_stdio.h"
#include "utgenstub.h"

void UT_DefaultHandler_PCS_fgets(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_fopen(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_snprintf(void *, UT_EntryKey_t, const UT_StubContext_t *, va_list);
void UT_DefaultHandler_PCS_vsnprintf(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_fclose()
 * ----------------------------------------------------
 */
int PCS_fclose(PCS_FILE *stream)
{
    UT_GenStub_SetupReturnBuffer(PCS_fclose, int);

    UT_GenStub_AddParam(PCS_fclose, PCS_FILE *, stream);

    UT_GenStub_Execute(PCS_fclose, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_fclose, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_fgets()
 * ----------------------------------------------------
 */
char *PCS_fgets(char *s, int n, PCS_FILE *stream)
{
    UT_GenStub_SetupReturnBuffer(PCS_fgets, char *);

    UT_GenStub_AddParam(PCS_fgets, char *, s);
    UT_GenStub_AddParam(PCS_fgets, int, n);
    UT_GenStub_AddParam(PCS_fgets, PCS_FILE *, stream);

    UT_GenStub_Execute(PCS_fgets, Basic, UT_DefaultHandler_PCS_fgets);

    return UT_GenStub_GetReturnValue(PCS_fgets, char *);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_fopen()
 * ----------------------------------------------------
 */
PCS_FILE *PCS_fopen(const char *filename, const char *modes)
{
    UT_GenStub_SetupReturnBuffer(PCS_fopen, PCS_FILE *);

    UT_GenStub_AddParam(PCS_fopen, const char *, filename);
    UT_GenStub_AddParam(PCS_fopen, const char *, modes);

    UT_GenStub_Execute(PCS_fopen, Basic, UT_DefaultHandler_PCS_fopen);

    return UT_GenStub_GetReturnValue(PCS_fopen, PCS_FILE *);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_fputs()
 * ----------------------------------------------------
 */
int PCS_fputs(const char *s, PCS_FILE *stream)
{
    UT_GenStub_SetupReturnBuffer(PCS_fputs, int);

    UT_GenStub_AddParam(PCS_fputs, const char *, s);
    UT_GenStub_AddParam(PCS_fputs, PCS_FILE *, stream);

    UT_GenStub_Execute(PCS_fputs, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_fputs, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_perror()
 * ----------------------------------------------------
 */
void PCS_perror(const char *str)
{
    UT_GenStub_AddParam(PCS_perror, const char *, str);

    UT_GenStub_Execute(PCS_perror, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_printf()
 * ----------------------------------------------------
 */
int PCS_printf(const char *format, ...)
{
    va_list UtStub_ArgList;

    UT_GenStub_SetupReturnBuffer(PCS_printf, int);

    UT_GenStub_AddParam(PCS_printf, const char *, format);

    va_start(UtStub_ArgList, format);
    UT_GenStub_Execute(PCS_printf, Va, NULL, UtStub_ArgList);
    va_end(UtStub_ArgList);

    return UT_GenStub_GetReturnValue(PCS_printf, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_putchar()
 * ----------------------------------------------------
 */
int PCS_putchar(int c)
{
    UT_GenStub_SetupReturnBuffer(PCS_putchar, int);

    UT_GenStub_AddParam(PCS_putchar, int, c);

    UT_GenStub_Execute(PCS_putchar, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_putchar, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_remove()
 * ----------------------------------------------------
 */
int PCS_remove(const char *filename)
{
    UT_GenStub_SetupReturnBuffer(PCS_remove, int);

    UT_GenStub_AddParam(PCS_remove, const char *, filename);

    UT_GenStub_Execute(PCS_remove, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_remove, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_rename()
 * ----------------------------------------------------
 */
int PCS_rename(const char *old, const char *nw)
{
    UT_GenStub_SetupReturnBuffer(PCS_rename, int);

    UT_GenStub_AddParam(PCS_rename, const char *, old);
    UT_GenStub_AddParam(PCS_rename, const char *, nw);

    UT_GenStub_Execute(PCS_rename, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_rename, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_snprintf()
 * ----------------------------------------------------
 */
int PCS_snprintf(char *s, size_t maxlen, const char *format, ...)
{
    va_list UtStub_ArgList;

    UT_GenStub_SetupReturnBuffer(PCS_snprintf, int);

    UT_GenStub_AddParam(PCS_snprintf, char *, s);
    UT_GenStub_AddParam(PCS_snprintf, size_t, maxlen);
    UT_GenStub_AddParam(PCS_snprintf, const char *, format);

    va_start(UtStub_ArgList, format);
    UT_GenStub_Execute(PCS_snprintf, Va, UT_DefaultHandler_PCS_snprintf, UtStub_ArgList);
    va_end(UtStub_ArgList);

    return UT_GenStub_GetReturnValue(PCS_snprintf, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_vsnprintf()
 * ----------------------------------------------------
 */
int PCS_vsnprintf(char *s, size_t maxlen, const char *format, PCS_va_list arg)
{
    UT_GenStub_SetupReturnBuffer(PCS_vsnprintf, int);

    UT_GenStub_AddParam(PCS_vsnprintf, char *, s);
    UT_GenStub_AddParam(PCS_vsnprintf, size_t, maxlen);
    UT_GenStub_AddParam(PCS_vsnprintf, const char *, format);
    UT_GenStub_AddParam(PCS_vsnprintf, PCS_va_list, arg);

    UT_GenStub_Execute(PCS_vsnprintf, Basic, UT_DefaultHandler_PCS_vsnprintf);

    return UT_GenStub_GetReturnValue(PCS_vsnprintf, int);
}
