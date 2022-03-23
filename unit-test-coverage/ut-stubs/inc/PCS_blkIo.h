/* PSP coverage stub basic data types */
#ifndef PCS_BLKIO_H
#define PCS_BLKIO_H

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"

/* The module and blk_dev types are used in several headers */
typedef struct PCS_BLK_DEV
{
    int bd;
} PCS_BLK_DEV;
typedef PCS_BLK_DEV *PCS_BLK_DEV_ID;

#endif
