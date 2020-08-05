/* PSP coverage stub replacement for vxPpcLib.h */
#ifndef _PSP_STUB_VXPPCLIB_H_
#define _PSP_STUB_VXPPCLIB_H_

#include <PCS_basetypes.h>

/* ----------------------------------------- */
/* constants normally defined in vxPpcLib.h */
/* ----------------------------------------- */

#define PCS_PPC_MSR_EE    0x2101
#define PCS_PPC_MSR_FP    0x2102
#define PCS_PPC_MSR_ME    0x2104
#define PCS_PPC_MSR_FE0   0x2108
#define PCS_PPC_MSR_FE1   0x2110
#define PCS_PPC_MSR_DR    0x2120

#define PCS_PPC_FPSCR_VE    0x2201
#define PCS_PPC_FPSCR_OE    0x2202
#define PCS_PPC_FPSCR_NI    0x2204
#define PCS_PPC_FPSCR_ZE    0x2208
#define PCS_PPC_FPSCR_XE    0x2210
#define PCS_PPC_FPSCR_UE    0x2220


/* ----------------------------------------- */
/* types normally defined in vxPpcLib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in vxPpcLib.h */
/* ----------------------------------------- */
extern void PCS_vxTimeBaseGet (uint32_t *u, uint32_t *l);
extern void PCS_vxMsrSet (uint32_t);
extern uint32_t PCS_vxMsrGet (void);
extern void PCS_vxFpscrSet (uint32_t);
extern uint32_t PCS_vxFpscrGet (void);
extern uint32_t PCS_vxDecGet (void);

#endif /* _PSP_STUB_VXPPCLIB_H_ */

