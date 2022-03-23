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
