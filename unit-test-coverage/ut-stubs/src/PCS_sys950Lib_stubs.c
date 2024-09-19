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
 * Auto-Generated stub implementations for functions defined in PCS_sys950Lib header
 */

#include "PCS_sys950Lib.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_GetUsecTime()
 * ----------------------------------------------------
 */
double PCS_GetUsecTime(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_GetUsecTime, double);

    UT_GenStub_Execute(PCS_GetUsecTime, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_GetUsecTime, double);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_getCoreClockSpeed()
 * ----------------------------------------------------
 */
uint32_t PCS_getCoreClockSpeed(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_getCoreClockSpeed, uint32_t);

    UT_GenStub_Execute(PCS_getCoreClockSpeed, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_getCoreClockSpeed, uint32_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_sysGetSlotId()
 * ----------------------------------------------------
 */
int PCS_sysGetSlotId(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_sysGetSlotId, int);

    UT_GenStub_Execute(PCS_sysGetSlotId, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_sysGetSlotId, int);
}
