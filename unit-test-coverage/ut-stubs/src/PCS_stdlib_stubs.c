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
 * Auto-Generated stub implementations for functions defined in PCS_stdlib header
 */

#include "PCS_stdlib.h"
#include "utgenstub.h"

void UT_DefaultHandler_PCS_free(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_malloc(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_strtoul(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_abort()
 * ----------------------------------------------------
 */
void PCS_abort(void)
{

    UT_GenStub_Execute(PCS_abort, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_abs()
 * ----------------------------------------------------
 */
int PCS_abs(int value)
{
    UT_GenStub_SetupReturnBuffer(PCS_abs, int);

    UT_GenStub_AddParam(PCS_abs, int, value);

    UT_GenStub_Execute(PCS_abs, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_abs, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_exit()
 * ----------------------------------------------------
 */
void PCS_exit(int status)
{
    UT_GenStub_AddParam(PCS_exit, int, status);

    UT_GenStub_Execute(PCS_exit, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_free()
 * ----------------------------------------------------
 */
void PCS_free(void *ptr)
{
    UT_GenStub_AddParam(PCS_free, void *, ptr);

    UT_GenStub_Execute(PCS_free, Basic, UT_DefaultHandler_PCS_free);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_malloc()
 * ----------------------------------------------------
 */
void *PCS_malloc(size_t sz)
{
    UT_GenStub_SetupReturnBuffer(PCS_malloc, void *);

    UT_GenStub_AddParam(PCS_malloc, size_t, sz);

    UT_GenStub_Execute(PCS_malloc, Basic, UT_DefaultHandler_PCS_malloc);

    return UT_GenStub_GetReturnValue(PCS_malloc, void *);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_strtoul()
 * ----------------------------------------------------
 */
unsigned long int PCS_strtoul(const char *nptr, char **endptr, int base)
{
    UT_GenStub_SetupReturnBuffer(PCS_strtoul, unsigned long int);

    UT_GenStub_AddParam(PCS_strtoul, const char *, nptr);
    UT_GenStub_AddParam(PCS_strtoul, char **, endptr);
    UT_GenStub_AddParam(PCS_strtoul, int, base);

    UT_GenStub_Execute(PCS_strtoul, Basic, UT_DefaultHandler_PCS_strtoul);

    return UT_GenStub_GetReturnValue(PCS_strtoul, unsigned long int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_system()
 * ----------------------------------------------------
 */
int PCS_system(const char *command)
{
    UT_GenStub_SetupReturnBuffer(PCS_system, int);

    UT_GenStub_AddParam(PCS_system, const char *, command);

    UT_GenStub_Execute(PCS_system, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_system, int);
}
