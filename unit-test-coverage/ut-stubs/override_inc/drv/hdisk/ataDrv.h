/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for drv/hdisk/ataDrv.h */
#ifndef _PSP_OVERRIDE_DRV_HDISK_ATADRV_H_
#define _PSP_OVERRIDE_DRV_HDISK_ATADRV_H_

#include "PCS_drv_hdisk_ataDrv.h"
#include <vxWorks.h>
#include <blkIo.h>

/* ----------------------------------------- */
/* mappings for declarations in drv/hdisk/ataDrv.h */
/* ----------------------------------------- */
#define ataDevCreate    PCS_ataDevCreate
#define ataXbdDevCreate PCS_ataXbdDevCreate

#endif /* _PSP_OVERRIDE_DRV_HDISK_ATADRV_H_ */
