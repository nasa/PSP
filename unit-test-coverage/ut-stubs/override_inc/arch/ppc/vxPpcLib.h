/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for vxPpcLib.h */
#ifndef _PSP_OVERRIDE_VXPPCLIB_H_
#define _PSP_OVERRIDE_VXPPCLIB_H_

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

#endif /* _PSP_OVERRIDE_VXPPCLIB_H_ */
