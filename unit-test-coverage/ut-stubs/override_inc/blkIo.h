/* PSP coverage stub replacement for blkIo.h */
#ifndef OVERRIDE_BLKIO_H
#define OVERRIDE_BLKIO_H

#include "PCS_blkIo.h"
#include <vxWorks.h>

/* ---------------------------------------*/
/* mappings for declarations in blkIo.h */
/* ---------------------------------------*/
#define NULLDEV    PCS_NULLDEV
#define BLK_DEV    PCS_BLK_DEV
#define BLK_DEV_ID PCS_BLK_DEV_ID

#endif
