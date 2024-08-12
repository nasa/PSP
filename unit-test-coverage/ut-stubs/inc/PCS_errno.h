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

/************************************************************************
 * Note that this file has been cloned-n-owned from its open-source github
 * repository for Gateway as of September 2023. Therefore, it is subject to
 * NASA Export Control restrictions, as stated below.
 ************************************************************************/

/************************************************************************/
/** \export_control EAR ECCN 9E515.a and/or 9E515.f (HALO)
 *
 * Export Administration Regulations (EAR) Notice
 *
 * This document contains information which falls under the purview of the
 * Export Administration Regulations (EAR), 15 CFR §730-774 and is export
 * controlled. It may be used only to fulfill responsibilities of the Parties
 * of, or a Cooperating Agency of a NASA Gateway Program Partner (CSA, ESA,
 * JAXA, MBRSC) and their contractors in furtherance of the Gateway MOUs
 * with ESA, CSA, and Japan and IA with MBRSC. Any use, re-transfer, or
 * disclosure to any party for any purpose other than the designated use of
 * fulfilling the responsibilities of the Gateway MOUs and IA requires prior
 * U.S. Government authorization.
 *************************************************************************/

/**
 * \file
 * \ingroup ut-stubs
 *
 * OSAL coverage stub replacement for errno.h
 */

#ifndef PCS_ERRNO_H
#define PCS_ERRNO_H

#include "PCS_basetypes.h"

/* ----------------------------------------- */
/* constants normally defined in errno.h */
/* ----------------------------------------- */
/* POSIX-specific  errnos */
#define PCS_EINTR     0x1801
#define PCS_EAGAIN    0x1802
#define PCS_EEXIST    0x180a
#define PCS_EINVAL    0x1803
#define PCS_EMSGSIZE  0x1804
#define PCS_ETIMEDOUT 0x1805
#define PCS_ESPIPE    0x1806
#define PCS_ENOTSUP   0x1807
#define PCS_ENOSYS    0x1808
#define PCS_EROFS     0x1809
#define PCS_EBADF     0x180b
#define PCS_ENOENT    0x180c

/* ----------------------------------------- */
/* types normally defined in errno.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in errno.h */
/* ----------------------------------------- */

extern int PCS_errno;

#endif /* PCS_ERRNO_H */
