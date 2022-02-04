/* PSP coverage stub replacement for rebootLib.h */
#ifndef PCS_REBOOTLIB_H
#define PCS_REBOOTLIB_H

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

#endif
