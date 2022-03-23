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

/* PSP coverage stub replacement for vxLib.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_vxLib.h"
#include "PCS_arch_ppc_vxPpcLib.h"

void PCS_vxTimeBaseGet(uint32_t *u, uint32_t *l)
{
    UT_Stub_RegisterContextGenericArg(UT_KEY(PCS_vxTimeBaseGet), u);
    UT_Stub_RegisterContextGenericArg(UT_KEY(PCS_vxTimeBaseGet), l);
    *u = 0;
    *l = 0;
    UT_DEFAULT_IMPL(PCS_vxTimeBaseGet);
}
void PCS_vxMsrSet(uint32_t val)
{
    UT_DEFAULT_IMPL(PCS_vxMsrSet);
}
uint32_t PCS_vxMsrGet(void)
{
    return UT_DEFAULT_IMPL(PCS_vxMsrGet);
}
void PCS_vxFpscrSet(uint32_t val)
{
    UT_DEFAULT_IMPL(PCS_vxFpscrSet);
}
uint32_t PCS_vxFpscrGet(void)
{
    return UT_DEFAULT_IMPL(PCS_vxFpscrGet);
}
uint32_t PCS_vxDecGet(void)
{
    return UT_DEFAULT_IMPL(PCS_vxDecGet);
}
