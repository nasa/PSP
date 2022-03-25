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
#ifndef OVERRIDE_MCPX750_H
#define OVERRIDE_MCPX750_H

#include "PCS_mcpx750.h"

/* ----------------------------------------- */
/* mappings for declarations in mcpx750.h */
/* ----------------------------------------- */
#define SYS_REG_BLRR        PCS_SYS_REG_BLRR
#define SYS_REG_BLRR_PWRON  PCS_SYS_REG_BLRR_PWRON
#define SYS_REG_BLRR_PBRST  PCS_SYS_REG_BLRR_PBRST
#define SYS_REG_BLRR_FBTN   PCS_SYS_REG_BLRR_FBTN
#define SYS_REG_BLRR_WDT2   PCS_SYS_REG_BLRR_WDT2
#define SYS_REG_BLRR_SWSRST PCS_SYS_REG_BLRR_SWSRST
#define SYS_REG_BLRR_SWHRST PCS_SYS_REG_BLRR_SWHRST

#define PCI_OUT_BYTE  PCS_PciOutByte
#define PCI_OUT_LONG  PCS_PciOutLong
#define sysPciWrite32 PCS_sysPciWrite32
#define sysPciRead32  PCS_sysPciRead32

#endif
