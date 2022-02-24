/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for moduleLib.h */
#ifndef OVERRIDE_MODULELIB_H
#define OVERRIDE_MODULELIB_H

#include "PCS_moduleLib.h"
#include <vxWorks.h>

/* ----------------------------------------- */
/* mappings for declarations in moduleLib.h */
/* ----------------------------------------- */

#define MODULE_ID   PCS_MODULE_ID
#define MODULE_INFO PCS_MODULE_INFO

#define moduleInfoGet    PCS_moduleInfoGet
#define moduleFindByName PCS_moduleFindByName

#endif
