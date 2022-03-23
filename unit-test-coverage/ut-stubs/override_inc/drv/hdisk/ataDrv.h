/* PSP coverage stub replacement for drv/hdisk/ataDrv.h */
#ifndef OVERRIDE_DRV_HDISK_ATADRV_H
#define OVERRIDE_DRV_HDISK_ATADRV_H

#include "PCS_drv_hdisk_ataDrv.h"
#include <vxWorks.h>
#include <blkIo.h>

/* ----------------------------------------- */
/* mappings for declarations in drv/hdisk/ataDrv.h */
/* ----------------------------------------- */
#define ataDevCreate    PCS_ataDevCreate
#define ataXbdDevCreate PCS_ataXbdDevCreate

#endif
