/* PSP coverage stub replacement for ramDrv.h */
#ifndef PCS_RAMDRV_H
#define PCS_RAMDRV_H

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"
#include "PCS_blkIo.h"

/* ----------------------------------------- */
/* constants normally defined in ramDrv.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in ramDrv.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in ramDrv.h */
/* ----------------------------------------- */
extern PCS_BLK_DEV *PCS_ramDevCreate(char *ramAddr, int bytesPerSec, int secPerTrack, int nSectors, int secOffset);

#endif
