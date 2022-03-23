/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/* PSP coverage stub replacement for xbdBlkDev.h */
#ifndef PCS_XBDBLKDEV_H
#define PCS_XBDBLKDEV_H

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

#endif
