/* PSP coverage stub replacement for xbdBlkDev.h */
#ifndef OVERRIDE_XBDBLKDEV_H
#define OVERRIDE_XBDBLKDEV_H

#include "PCS_xbdBlkDev.h"
#include <vxWorks.h>
#include <blkIo.h>

/* ----------------------------------------- */
/* mappings for declarations in xbdBlkDev.h */
/* ----------------------------------------- */

#define NULLDEV             PCS_NULLDEV
#define device_t            PCS_device_t
#define xbdBlkDevCreateSync PCS_xbdBlkDevCreateSync
#define xbdBlkDevDelete     PCS_xbdBlkDevDelete

#endif
