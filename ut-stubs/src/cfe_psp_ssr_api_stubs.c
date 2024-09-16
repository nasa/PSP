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
 * Auto-Generated stub implementations for functions defined in cfe_psp_ssr_api header
 */

#include "cfe_psp_ssr_api.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_InitSSR()
 * ----------------------------------------------------
 */
int32 CFE_PSP_InitSSR(uint32 bus, uint32 device, char *DeviceName)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_InitSSR, int32);

    UT_GenStub_AddParam(CFE_PSP_InitSSR, uint32, bus);
    UT_GenStub_AddParam(CFE_PSP_InitSSR, uint32, device);
    UT_GenStub_AddParam(CFE_PSP_InitSSR, char *, DeviceName);

    UT_GenStub_Execute(CFE_PSP_InitSSR, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_InitSSR, int32);
}
