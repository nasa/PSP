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

/* PSP coverage stub replacement for unistd.h */
#ifndef OVERRIDE_UNISTD_H
#define OVERRIDE_UNISTD_H

#include "PCS_unistd.h"

/* ----------------------------------------- */
/* mappings for declarations in unistd.h */
/* ----------------------------------------- */

#define SEEK_SET      PCS_SEEK_SET
#define SEEK_CUR      PCS_SEEK_CUR
#define SEEK_END      PCS_SEEK_END
#define STDIN_FILENO  PCS_STDIN_FILENO
#define STDOUT_FILENO PCS_STDOUT_FILENO
#define STDERR_FILENO PCS_STDERR_FILENO

#define close       PCS_close
#define getegid     PCS_getegid
#define geteuid     PCS_geteuid
#define gethostid   PCS_gethostid
#define gethostname PCS_gethostname
#define getpid      PCS_getpid
#define lseek       PCS_lseek
#define read        PCS_read
#define rmdir       PCS_rmdir
#define sysconf     PCS_sysconf
#define write       PCS_write

#endif
