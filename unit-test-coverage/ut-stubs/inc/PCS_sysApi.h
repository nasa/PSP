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

/************************************************************************
 * Note that this file has been cloned-n-owned from its open-source github
 * repository for Gateway as of September 2023. Therefore, it is subject to
 * NASA Export Control restrictions, as stated below.
 ************************************************************************/

/************************************************************************/
/** \export_control EAR ECCN 9E515.a and/or 9E515.f (HALO)
 *
 * Export Administration Regulations (EAR) Notice
 *
 * This document contains information which falls under the purview of the
 * Export Administration Regulations (EAR), 15 CFR §730-774 and is export
 * controlled. It may be used only to fulfill responsibilities of the Parties
 * of, or a Cooperating Agency of a NASA Gateway Program Partner (CSA, ESA,
 * JAXA, MBRSC) and their contractors in furtherance of the Gateway MOUs
 * with ESA, CSA, and Japan and IA with MBRSC. Any use, re-transfer, or
 * disclosure to any party for any purpose other than the designated use of
 * fulfilling the responsibilities of the Gateway MOUs and IA requires prior
 * U.S. Government authorization.
 *************************************************************************/

/* PSP coverage stub replacement for sysApi.h */
#ifndef PCS_SYSAPI_H
#define PCS_SYSAPI_H

#include "common_types.h"

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"

/* ----------------------------------------- */
/* constants normally defined in sysApi.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in sysApi.h */
/* ----------------------------------------- */
typedef enum
{
    SP0_100 = 1,
    SP0_200 = 2
} PCS_SP0_BOARD_LEVEL_TYPE;

typedef enum
{
    SP0_ORIGINAL = 1,
    SP0_UPGRADE  = 2
} PCS_SP0_BOARD_GENERATION_TYPE;

/* ----------------------------------------- */
/* prototypes normally declared in sysApi.h */
/* ----------------------------------------- */
int  PCS_sysEnableFpgaWdt(bool globalReset);
int  PCS_sysDisableFpgaWdt(void);
int  PCS_sysSetFpgaWdt(float secs);
void PCS_sysPulseFpgaWdt(void);

bool PCS_isCpciSysController(void);

PCS_SP0_BOARD_GENERATION_TYPE PCS_sysGetBoardGeneration(bool talkative);

#endif
