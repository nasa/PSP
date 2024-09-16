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
 * Auto-Generated stub implementations for functions defined in PCS_cfe_configdata header
 */

#include "PCS_cfe_configdata.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_System1HzISR()
 * ----------------------------------------------------
 */
void PCS_System1HzISR(void)
{

    UT_GenStub_Execute(PCS_System1HzISR, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_SystemMain()
 * ----------------------------------------------------
 */
void PCS_SystemMain(uint32_t StartType, uint32_t StartSubtype, uint32_t ModeId, const char *StartFilePath)
{
    UT_GenStub_AddParam(PCS_SystemMain, uint32_t, StartType);
    UT_GenStub_AddParam(PCS_SystemMain, uint32_t, StartSubtype);
    UT_GenStub_AddParam(PCS_SystemMain, uint32_t, ModeId);
    UT_GenStub_AddParam(PCS_SystemMain, const char *, StartFilePath);

    UT_GenStub_Execute(PCS_SystemMain, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_SystemNotify()
 * ----------------------------------------------------
 */
void PCS_SystemNotify(void)
{

    UT_GenStub_Execute(PCS_SystemNotify, Basic, NULL);
}
