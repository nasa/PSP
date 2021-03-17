/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for sysLib.h */
#ifndef _PSP_OVERRIDE_SYSLIB_H_
#define _PSP_OVERRIDE_SYSLIB_H_

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

#endif /* _PSP_OVERRIDE_SYSLIB_H_ */
