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
 * Auto-Generated stub implementations for functions defined in PCS_sysApi header
 */

#include "PCS_sysApi.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_isCpciSysController()
 * ----------------------------------------------------
 */
bool PCS_isCpciSysController(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_isCpciSysController, bool);

    UT_GenStub_Execute(PCS_isCpciSysController, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_isCpciSysController, bool);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_sysDisableFpgaWdt()
 * ----------------------------------------------------
 */
int PCS_sysDisableFpgaWdt(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_sysDisableFpgaWdt, int);

    UT_GenStub_Execute(PCS_sysDisableFpgaWdt, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_sysDisableFpgaWdt, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_sysEnableFpgaWdt()
 * ----------------------------------------------------
 */
int PCS_sysEnableFpgaWdt(bool globalReset)
{
    UT_GenStub_SetupReturnBuffer(PCS_sysEnableFpgaWdt, int);

    UT_GenStub_AddParam(PCS_sysEnableFpgaWdt, bool, globalReset);

    UT_GenStub_Execute(PCS_sysEnableFpgaWdt, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_sysEnableFpgaWdt, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_sysGetBoardGeneration()
 * ----------------------------------------------------
 */
PCS_SP0_BOARD_GENERATION_TYPE PCS_sysGetBoardGeneration(bool talkative)
{
    UT_GenStub_SetupReturnBuffer(PCS_sysGetBoardGeneration, PCS_SP0_BOARD_GENERATION_TYPE);

    UT_GenStub_AddParam(PCS_sysGetBoardGeneration, bool, talkative);

    UT_GenStub_Execute(PCS_sysGetBoardGeneration, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_sysGetBoardGeneration, PCS_SP0_BOARD_GENERATION_TYPE);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_sysPulseFpgaWdt()
 * ----------------------------------------------------
 */
void PCS_sysPulseFpgaWdt(void)
{

    UT_GenStub_Execute(PCS_sysPulseFpgaWdt, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_sysSetFpgaWdt()
 * ----------------------------------------------------
 */
int PCS_sysSetFpgaWdt(float secs)
{
    UT_GenStub_SetupReturnBuffer(PCS_sysSetFpgaWdt, int);

    UT_GenStub_AddParam(PCS_sysSetFpgaWdt, float, secs);

    UT_GenStub_Execute(PCS_sysSetFpgaWdt, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_sysSetFpgaWdt, int);
}
