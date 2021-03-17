/* PSP coverage stub replacement for ramDrv.h */
#ifndef _PSP_STUB_RAMDRV_H_
#define _PSP_STUB_RAMDRV_H_

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

#endif /* _PSP_STUB_RAMDRV_H_ */
