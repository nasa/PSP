/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for blkIo.h */
#ifndef _PSP_OVERRIDE_BLKIO_H_
#define _PSP_OVERRIDE_BLKIO_H_

#include "PCS_blkIo.h"
#include <vxWorks.h>

/* ---------------------------------------*/
/* mappings for declarations in blkIo.h */
/* ---------------------------------------*/
#define NULLDEV    PCS_NULLDEV
#define BLK_DEV    PCS_BLK_DEV
#define BLK_DEV_ID PCS_BLK_DEV_ID

#endif /* _PSP_OVERRIDE_BLKIO_H_ */
