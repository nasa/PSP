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

/* PSP coverage stub replacement for sysLib.h */
#ifndef PCS_SYSLIB_H
#define PCS_SYSLIB_H

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"

/* ----------------------------------------- */
/* constants normally defined in sysLib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in sysLib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in sysLib.h */
/* ----------------------------------------- */
extern int   PCS_sysClkRateGet(void);
extern char *PCS_sysMemTop(void);

extern void PCS_PciOutByte(uint32_t address, uint8_t data);
extern void PCS_PciOutLong(uint32_t address, uint32_t data);
extern void PCS_sysPciWrite32(uint32_t address, uint32_t data);
extern void PCS_sysPciRead32(uint32_t address, uint32_t *data);

extern unsigned int PCS_GetWrsKernelTextStart(void);
extern unsigned int PCS_GetWrsKernelTextEnd(void);

#endif
