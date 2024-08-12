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
 * OSAL coverage stub replacement for fcntl.h
 */

#ifndef PCS_FCNTL_H
#define PCS_FCNTL_H

#include "PCS_basetypes.h"

#include "PCS_sys_types.h"

/* ----------------------------------------- */
/* constants normally defined in fcntl.h */
/* ----------------------------------------- */

/*
 * note these constants are used as bitmasks and so
 * they must be single bit flags to work properly.
 *
 * However, they are defined differently from a typical UNIX
 * in order to increase the likelihood that a hard-coded value
 * is caught by UT.
 *
 * These are exposed to apps through fcntl.h and sys/stat.h
 */
#define PCS_S_IRWXO 0x1110
#define PCS_S_IRWXG 0x2220
#define PCS_S_IRWXU 0x4440

#define PCS_S_IXOTH 0x1000
#define PCS_S_IXGRP 0x2000
#define PCS_S_IXUSR 0x4000

#define PCS_S_IROTH 0x0100
#define PCS_S_IRGRP 0x0200
#define PCS_S_IRUSR 0x0400

#define PCS_S_IWOTH 0x0010
#define PCS_S_IWGRP 0x0020
#define PCS_S_IWUSR 0x0040

#define PCS_S_IFDIR    0x0001
#define PCS_S_ISDIR(x) (((x)&PCS_S_IFDIR) == PCS_S_IFDIR)

#define PCS_O_RDONLY   0x1501
#define PCS_O_WRONLY   0x1502
#define PCS_O_RDWR     0x1503
#define PCS_O_CREAT    0x1504
#define PCS_O_TRUNC    0x1508
#define PCS_O_NONBLOCK 0x1510

#define PCS_F_GETFL 0x1D01
#define PCS_F_SETFL 0x1D02
#define PCS_F_GETFD 0x1D03
#define PCS_F_SETFD 0x1D04
#define PCS_F_DUPFD 0x1D05

/* ----------------------------------------- */
/* types normally defined in fcntl.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in fcntl.h */
/* ----------------------------------------- */

extern int PCS_fcntl(int fd, int cmd, ...);
extern int PCS_open(const char *file, int oflag, ...);
extern int PCS_creat(const char *pathname, PCS_mode_t mode);
extern int PCS_mkdir(const char *pathname);

#endif /* PCS_FCNTL_H */
