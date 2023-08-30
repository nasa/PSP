/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2023 United States Government as represented by the
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

/* PSP coverage stub replacement for spyLibP.h */
#ifndef PCS_SPYLIBP_H
#define PCS_SPYLIBP_H

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"

/* ----------------------------------------- */
/* constants normally defined in spyLibP.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in spyLibP.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in spyLibP.h */
/* ----------------------------------------- */
void PCS_spyReportCommon(PCS_FUNCPTR print);
void PCS_spyClkStopCommon(void);
int  PCS_spyClkStartCommon(int intsPerSec, PCS_FUNCPTR print);


#endif
