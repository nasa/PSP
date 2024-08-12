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

/* PSP coverage stub replacement for fcntl.h */
#ifndef OVERRIDE_FCNTL_H
#define OVERRIDE_FCNTL_H

#include "PCS_fcntl.h"

/* ----------------------------------------- */
/* mappings for declarations in fcntl.h */
/* ----------------------------------------- */

#define S_IRWXU    PCS_S_IRWXU
#define S_IRWXG    PCS_S_IRWXG
#define S_IRWXO    PCS_S_IRWXO
#define S_IXOTH    PCS_S_IXOTH
#define S_IXGRP    PCS_S_IXGRP
#define S_IXUSR    PCS_S_IXUSR
#define S_IROTH    PCS_S_IROTH
#define S_IRGRP    PCS_S_IRGRP
#define S_IRUSR    PCS_S_IRUSR
#define S_IWOTH    PCS_S_IWOTH
#define S_IWGRP    PCS_S_IWGRP
#define S_IWUSR    PCS_S_IWUSR
#define S_IFDIR    PCS_S_IFDIR
#define S_ISDIR(x) PCS_S_ISDIR(x)
#define F_GETFL    PCS_F_GETFL
#define F_SETFL    PCS_F_SETFL
#define F_GETFD    PCS_F_GETFD
#define F_SETFD    PCS_F_SETFD
#define F_DUPFD    PCS_F_DUPFD

#define O_RDONLY   PCS_O_RDONLY
#define O_WRONLY   PCS_O_WRONLY
#define O_CREAT    PCS_O_CREAT
#define O_RDWR     PCS_O_RDWR
#define O_TRUNC    PCS_O_TRUNC
#define O_NONBLOCK PCS_O_NONBLOCK

#define fcntl PCS_fcntl
#define open  PCS_open
#define creat PCS_creat
#define mkdir PCS_mkdir

#endif /* OVERRIDE_FCNTL_H */
