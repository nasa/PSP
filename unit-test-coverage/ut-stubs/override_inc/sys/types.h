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

/* PSP coverage stub replacement for sys/types.h */
#ifndef OVERRIDE_SYS_TYPES_H
#define OVERRIDE_SYS_TYPES_H

#include "PCS_sys_types.h"

/* ----------------------------------------- */
/* mappings for declarations in sys/types.h */
/* ----------------------------------------- */
#define ssize_t PCS_ssize_t
#define off_t   PCS_off_t
#define mode_t  PCS_mode_t
#define pid_t   PCS_pid_t
#define gid_t   PCS_gid_t
#define uid_t   PCS_uid_t

#endif
