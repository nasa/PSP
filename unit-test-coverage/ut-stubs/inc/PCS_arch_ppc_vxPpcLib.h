/* PSP coverage stub replacement for vxPpcLib.h */
#ifndef _PSP_STUB_VXPPCLIB_H_
#define _PSP_STUB_VXPPCLIB_H_

#include "PCS_basetypes.h"

/*
 * When building the coverage test on an actual VxWorks target,
 * these symbols are indirectly provided via the system limits.h file.
 * This results in a redefinition issue if the custom PCS definitions are used.
 */
#if defined(_VXWORKS_OS_) && defined(__PPC__)

#define PCS_PPC_MSR_EE  _PPC_MSR_EE
#define PCS_PPC_MSR_FP  _PPC_MSR_FP
#define PCS_PPC_MSR_ME  _PPC_MSR_ME
#define PCS_PPC_MSR_FE0 _PPC_MSR_FE0
#define PCS_PPC_MSR_FE1 _PPC_MSR_FE1
#define PCS_PPC_MSR_DR  _PPC_MSR_DR

#define PCS_PPC_FPSCR_VE _PPC_FPSCR_VE
#define PCS_PPC_FPSCR_OE _PPC_FPSCR_OE
#define PCS_PPC_FPSCR_NI _PPC_FPSCR_NI
#define PCS_PPC_FPSCR_ZE _PPC_FPSCR_ZE
#define PCS_PPC_FPSCR_XE _PPC_FPSCR_XE
#define PCS_PPC_FPSCR_UE _PPC_FPSCR_UE

#else

/* ----------------------------------------- */
/* constants normally defined in vxPpcLib.h */
/* ----------------------------------------- */

#define PCS_PPC_MSR_EE  0x2101
#define PCS_PPC_MSR_FP  0x2102
#define PCS_PPC_MSR_ME  0x2104
#define PCS_PPC_MSR_FE0 0x2108
#define PCS_PPC_MSR_FE1 0x2110
#define PCS_PPC_MSR_DR  0x2120

#define PCS_PPC_FPSCR_VE 0x2201
#define PCS_PPC_FPSCR_OE 0x2202
#define PCS_PPC_FPSCR_NI 0x2204
#define PCS_PPC_FPSCR_ZE 0x2208
#define PCS_PPC_FPSCR_XE 0x2210
#define PCS_PPC_FPSCR_UE 0x2220

#endif

/* ----------------------------------------- */
/* types normally defined in vxPpcLib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in vxPpcLib.h */
/* ----------------------------------------- */
extern void     PCS_vxTimeBaseGet(uint32_t *u, uint32_t *l);
extern void     PCS_vxMsrSet(uint32_t);
extern uint32_t PCS_vxMsrGet(void);
extern void     PCS_vxFpscrSet(uint32_t);
extern uint32_t PCS_vxFpscrGet(void);
extern uint32_t PCS_vxDecGet(void);

#endif /* _PSP_STUB_VXPPCLIB_H_ */
