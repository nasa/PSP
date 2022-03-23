/* PSP coverage stub replacement for rebootLib.h */
#ifndef OVERRIDE_REBOOTLIB_H
#define OVERRIDE_REBOOTLIB_H

#include "PCS_rebootLib.h"

/* ----------------------------------------- */
/* mappings for declarations in rebootLib.h */
/* ----------------------------------------- */
#define BOOT_CLEAR  PCS_BOOT_CLEAR
#define BOOT_NORMAL PCS_BOOT_NORMAL

#define reboot PCS_reboot

#endif
