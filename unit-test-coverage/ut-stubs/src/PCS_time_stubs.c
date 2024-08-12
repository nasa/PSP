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
 * Auto-Generated stub implementations for functions defined in PCS_time header
 */

#include "PCS_time.h"
#include "utgenstub.h"

void UT_DefaultHandler_PCS_clock_gettime(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_clock_gettime()
 * ----------------------------------------------------
 */
int PCS_clock_gettime(int clk_id, struct PCS_timespec *t)
{
    UT_GenStub_SetupReturnBuffer(PCS_clock_gettime, int);

    UT_GenStub_AddParam(PCS_clock_gettime, int, clk_id);
    UT_GenStub_AddParam(PCS_clock_gettime, struct PCS_timespec *, t);

    UT_GenStub_Execute(PCS_clock_gettime, Basic, UT_DefaultHandler_PCS_clock_gettime);

    return UT_GenStub_GetReturnValue(PCS_clock_gettime, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_clock_settime()
 * ----------------------------------------------------
 */
int PCS_clock_settime(int clk_id, struct PCS_timespec *t)
{
    UT_GenStub_SetupReturnBuffer(PCS_clock_settime, int);

    UT_GenStub_AddParam(PCS_clock_settime, int, clk_id);
    UT_GenStub_AddParam(PCS_clock_settime, struct PCS_timespec *, t);

    UT_GenStub_Execute(PCS_clock_settime, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_clock_settime, int);
}
