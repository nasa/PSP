/* PSP coverage stub replacement for drv/hdisk/ataDrv.h */
#ifndef PCS_DRV_HDISK_ATADRV_H
#define PCS_DRV_HDISK_ATADRV_H

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"
#include "PCS_blkIo.h"
#include "PCS_xbdBlkDev.h"

/* ----------------------------------------- */
/* constants normally defined in drv/hdisk/ataDrv.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in drv/hdisk/ataDrv.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in drv/hdisk/ataDrv.h */
/* ----------------------------------------- */
extern PCS_device_t PCS_ataXbdDevCreate(int ctrl, int drive, unsigned int nBlks, unsigned int offset, const char *);

#endif
