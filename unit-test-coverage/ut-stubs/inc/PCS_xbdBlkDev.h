/* PSP coverage stub replacement for xbdBlkDev.h */
#ifndef _PSP_STUB_XBDBLKDEV_H_
#define _PSP_STUB_XBDBLKDEV_H_

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"
#include "PCS_blkIo.h"

/* ----------------------------------------- */
/* constants normally defined in xbdBlkDev.h */
/* ----------------------------------------- */
#define PCS_NULLDEV ((PCS_device_t)0)

/* ----------------------------------------- */
/* types normally defined in xbdBlkDev.h */
/* ----------------------------------------- */
typedef int PCS_device_t;

/* ----------------------------------------- */
/* prototypes normally declared in xbdBlkDev.h */
/* ----------------------------------------- */
extern PCS_device_t PCS_xbdBlkDevCreateSync(PCS_BLK_DEV *bd, const char *name);
extern PCS_STATUS   PCS_xbdBlkDevDelete(PCS_device_t dev, PCS_BLK_DEV **ppbd);

#endif /* _PSP_STUB_XBDBLKDEV_H_ */
