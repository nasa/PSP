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
