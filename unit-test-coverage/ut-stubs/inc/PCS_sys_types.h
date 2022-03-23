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
#ifndef PCS_SYS_TYPES_H
#define PCS_SYS_TYPES_H

#include "PCS_basetypes.h"

/* ----------------------------------------- */
/* constants normally defined in sys/types.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in sys/types.h */
/* ----------------------------------------- */
typedef ptrdiff_t    PCS_ssize_t;
typedef size_t       PCS_off_t;
typedef unsigned int PCS_mode_t;
typedef long         PCS_time_t;
typedef int          PCS_pid_t;
typedef int          PCS_gid_t;
typedef int          PCS_uid_t;

/* ----------------------------------------- */
/* prototypes normally declared in sys/types.h */
/* ----------------------------------------- */

#endif
