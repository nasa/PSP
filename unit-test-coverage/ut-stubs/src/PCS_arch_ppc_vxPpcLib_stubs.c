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
 * Auto-Generated stub implementations for functions defined in PCS_arch_ppc_vxPpcLib header
 */

#include "PCS_arch_ppc_vxPpcLib.h"
#include "utgenstub.h"

void UT_DefaultHandler_PCS_vxTimeBaseGet(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_vxDecGet()
 * ----------------------------------------------------
 */
uint32_t PCS_vxDecGet(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_vxDecGet, uint32_t);

    UT_GenStub_Execute(PCS_vxDecGet, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_vxDecGet, uint32_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_vxFpscrGet()
 * ----------------------------------------------------
 */
uint32_t PCS_vxFpscrGet(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_vxFpscrGet, uint32_t);

    UT_GenStub_Execute(PCS_vxFpscrGet, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_vxFpscrGet, uint32_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_vxFpscrSet()
 * ----------------------------------------------------
 */
void PCS_vxFpscrSet(uint32_t r)
{
    UT_GenStub_AddParam(PCS_vxFpscrSet, uint32_t, r);

    UT_GenStub_Execute(PCS_vxFpscrSet, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_vxMsrGet()
 * ----------------------------------------------------
 */
uint32_t PCS_vxMsrGet(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_vxMsrGet, uint32_t);

    UT_GenStub_Execute(PCS_vxMsrGet, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_vxMsrGet, uint32_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_vxMsrSet()
 * ----------------------------------------------------
 */
void PCS_vxMsrSet(uint32_t r)
{
    UT_GenStub_AddParam(PCS_vxMsrSet, uint32_t, r);

    UT_GenStub_Execute(PCS_vxMsrSet, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_vxTimeBaseGet()
 * ----------------------------------------------------
 */
void PCS_vxTimeBaseGet(uint32_t *u, uint32_t *l)
{
    UT_GenStub_AddParam(PCS_vxTimeBaseGet, uint32_t *, u);
    UT_GenStub_AddParam(PCS_vxTimeBaseGet, uint32_t *, l);

    UT_GenStub_Execute(PCS_vxTimeBaseGet, Basic, UT_DefaultHandler_PCS_vxTimeBaseGet);
}
