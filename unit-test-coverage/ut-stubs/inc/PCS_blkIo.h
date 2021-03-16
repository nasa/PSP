/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub basic data types */
#ifndef _PSP_STUB_BLKIO_H_
#define _PSP_STUB_BLKIO_H_

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"

/* The module and blk_dev types are used in several headers */
typedef struct PCS_BLK_DEV
{
    int bd;
} PCS_BLK_DEV;
typedef PCS_BLK_DEV *PCS_BLK_DEV_ID;

#endif /* _PSP_STUB_BLKIO_H_ */
