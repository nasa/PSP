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
 * Auto-Generated stub implementations for functions defined in PCS_object header
 */

#include "PCS_object.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_rtems_build_name()
 * ----------------------------------------------------
 */
uint32_t PCS_rtems_build_name(char A, char B, char C, char D)
{
    UT_GenStub_SetupReturnBuffer(PCS_rtems_build_name, uint32_t);

    UT_GenStub_AddParam(PCS_rtems_build_name, char, A);
    UT_GenStub_AddParam(PCS_rtems_build_name, char, B);
    UT_GenStub_AddParam(PCS_rtems_build_name, char, C);
    UT_GenStub_AddParam(PCS_rtems_build_name, char, D);

    UT_GenStub_Execute(PCS_rtems_build_name, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_rtems_build_name, uint32_t);
}
