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
 * Auto-Generated stub implementations for functions defined in PCS_ramDrv header
 */

#include "PCS_ramDrv.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_ramDevCreate()
 * ----------------------------------------------------
 */
PCS_BLK_DEV *PCS_ramDevCreate(char *ramAddr, int bytesPerSec, int secPerTrack, int nSectors, int secOffset)
{
    UT_GenStub_SetupReturnBuffer(PCS_ramDevCreate, PCS_BLK_DEV *);

    UT_GenStub_AddParam(PCS_ramDevCreate, char *, ramAddr);
    UT_GenStub_AddParam(PCS_ramDevCreate, int, bytesPerSec);
    UT_GenStub_AddParam(PCS_ramDevCreate, int, secPerTrack);
    UT_GenStub_AddParam(PCS_ramDevCreate, int, nSectors);
    UT_GenStub_AddParam(PCS_ramDevCreate, int, secOffset);

    UT_GenStub_Execute(PCS_ramDevCreate, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_ramDevCreate, PCS_BLK_DEV *);
}
