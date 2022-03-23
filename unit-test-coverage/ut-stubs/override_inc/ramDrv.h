/* PSP coverage stub replacement for ramDrv.h */
#ifndef OVERRIDE_RAMDRV_H
#define OVERRIDE_RAMDRV_H

#include "PCS_ramDrv.h"
#include <vxWorks.h>
#include <blkIo.h>

/* ----------------------------------------- */
/* mappings for declarations in ramDrv.h */
/* ----------------------------------------- */

#define ramDevCreate PCS_ramDevCreate

#endif
