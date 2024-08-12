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
 * Auto-Generated stub implementations for functions defined in PCS_arpa_inet header
 */

#include "PCS_arpa_inet.h"
#include "utgenstub.h"

void UT_DefaultHandler_PCS_inet_addr(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_inet_ntoa(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_inet_addr()
 * ----------------------------------------------------
 */
uint32_t PCS_inet_addr(const char *cp)
{
    UT_GenStub_SetupReturnBuffer(PCS_inet_addr, uint32_t);

    UT_GenStub_AddParam(PCS_inet_addr, const char *, cp);

    UT_GenStub_Execute(PCS_inet_addr, Basic, UT_DefaultHandler_PCS_inet_addr);

    return UT_GenStub_GetReturnValue(PCS_inet_addr, uint32_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_inet_ntoa()
 * ----------------------------------------------------
 */
char *PCS_inet_ntoa(struct PCS_in_addr in)
{
    UT_GenStub_SetupReturnBuffer(PCS_inet_ntoa, char *);

    UT_GenStub_AddParam(PCS_inet_ntoa, struct PCS_in_addr, in);

    UT_GenStub_Execute(PCS_inet_ntoa, Basic, UT_DefaultHandler_PCS_inet_ntoa);

    return UT_GenStub_GetReturnValue(PCS_inet_ntoa, char *);
}
