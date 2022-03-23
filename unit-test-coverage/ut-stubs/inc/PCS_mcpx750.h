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

/* PSP coverage stub replacement for mcpx750.h */
#ifndef PCS_MCPX750_H
#define PCS_MCPX750_H

#include "PCS_basetypes.h"

/* ----------------------------------------- */
/* constants normally defined in mcpx750.h */
/* ----------------------------------------- */
#define PCS_SYS_REG_BLRR_PWRON  0x01
#define PCS_SYS_REG_BLRR_PBRST  0x02
#define PCS_SYS_REG_BLRR_FBTN   0x04
#define PCS_SYS_REG_BLRR_WDT2   0x08
#define PCS_SYS_REG_BLRR_SWSRST 0x10
#define PCS_SYS_REG_BLRR_SWHRST 0x20

extern uint32_t *PCS_SYS_REG_BLRR;

/* ----------------------------------------- */
/* types normally defined in mcpx750.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in mcpx750.h */
/* ----------------------------------------- */

#endif
