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

/* PSP coverage stub replacement for vxPpcLib.h */
#ifndef OVERRIDE_VXPPCLIB_H
#define OVERRIDE_VXPPCLIB_H

#include "PCS_arch_ppc_vxPpcLib.h"

/*
 * When building the coverage test on an actual VxWorks target,
 * these symbols are indirectly provided via the system limits.h file.
 * This results in a redefinition issue if the custom PCS definitions are used.
 */
#if !defined(_VXWORKS_OS_) || !defined(__PPC__)

/* ----------------------------------------- */
/* mappings for declarations in vxPpcLib.h */
/* ----------------------------------------- */
#define _PPC_MSR_EE  PCS_PPC_MSR_EE
#define _PPC_MSR_FP  PCS_PPC_MSR_FP
#define _PPC_MSR_ME  PCS_PPC_MSR_ME
#define _PPC_MSR_FE0 PCS_PPC_MSR_FE0
#define _PPC_MSR_FE1 PCS_PPC_MSR_FE1
#define _PPC_MSR_DR  PCS_PPC_MSR_DR

#define _PPC_FPSCR_VE PCS_PPC_FPSCR_VE
#define _PPC_FPSCR_OE PCS_PPC_FPSCR_OE
#define _PPC_FPSCR_NI PCS_PPC_FPSCR_NI
#define _PPC_FPSCR_ZE PCS_PPC_FPSCR_ZE
#define _PPC_FPSCR_XE PCS_PPC_FPSCR_XE
#define _PPC_FPSCR_UE PCS_PPC_FPSCR_UE

#endif

#define vxTimeBaseGet PCS_vxTimeBaseGet

#define vxMsrSet   PCS_vxMsrSet
#define vxMsrGet   PCS_vxMsrGet
#define vxFpscrSet PCS_vxFpscrSet
#define vxFpscrGet PCS_vxFpscrGet
#define vxDecGet   PCS_vxDecGet

#endif
