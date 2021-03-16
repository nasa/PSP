/* PSP coverage stub replacement for rebootLib.h */
#ifndef _PSP_STUB_REBOOTLIB_H_
#define _PSP_STUB_REBOOTLIB_H_

#include "PCS_basetypes.h"

/* ----------------------------------------- */
/* constants normally defined in rebootLib.h */
/* ----------------------------------------- */
#define PCS_BOOT_CLEAR  0x2401
#define PCS_BOOT_NORMAL 0x2402

/* ----------------------------------------- */
/* types normally defined in rebootLib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in rebootLib.h */
/* ----------------------------------------- */
extern void PCS_reboot(int);

#endif /* _PSP_STUB_REBOOTLIB_H_ */
