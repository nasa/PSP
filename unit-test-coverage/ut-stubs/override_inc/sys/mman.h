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

/* PSP coverage stub replacement for sys/mman.h */
#ifndef OVERRIDE_SYS_MMAN_H
#define OVERRIDE_SYS_MMAN_H

#include "PCS_sys_mman.h"

/* ----------------------------------------- */
/* mappings for declarations in sys/mman.h */
/* ----------------------------------------- */

#define PROT_READ   PCS_PROT_READ
#define PROT_WRITE  PCS_PROT_WRITE
#define PROT_EXEC   PCS_PROT_EXEC
#define PROT_NONE   PCS_PROT_NONE
#define MAP_SHARED  PCS_MAP_SHARED
#define MAP_PRIVATE PCS_MAP_PRIVATE
#define MAP_FIXED   PCS_MAP_FIXED

#define off_t PCS_off_t
#define mmap  PCS_mmap

#endif
