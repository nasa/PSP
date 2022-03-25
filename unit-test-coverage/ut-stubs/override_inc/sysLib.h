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
#ifndef OVERRIDE_SYSLIB_H
#define OVERRIDE_SYSLIB_H

#include "PCS_sysLib.h"
#include <vxWorks.h>

/* ----------------------------------------- */
/* mappings for declarations in sysLib.h */
/* ----------------------------------------- */
#define sysClkRateGet PCS_sysClkRateGet
#define sysMemTop     PCS_sysMemTop

/*
 * These PCI accessors are related to sysLib but the prototype does not necessarily appear in this file
 */
#define PciOutByte    PCS_PciOutByte
#define PciOutLong    PCS_PciOutLong
#define sysPciWrite32 PCS_sysPciWrite32
#define sysPciRead32  PCS_sysPciRead32

/*
 * These definitions are part of BSP integration which does not have a header file
 */
#define GetWrsKernelTextStart PCS_GetWrsKernelTextStart
#define GetWrsKernelTextEnd   PCS_GetWrsKernelTextEnd

#endif
