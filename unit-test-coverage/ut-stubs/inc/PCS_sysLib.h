/* PSP coverage stub replacement for sysLib.h */
#ifndef _PSP_STUB_SYSLIB_H_
#define _PSP_STUB_SYSLIB_H_

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

#endif /* _PSP_STUB_SYSLIB_H_ */
