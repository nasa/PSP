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
#ifndef PCS_SYS_MMAN_H
#define PCS_SYS_MMAN_H

#include "PCS_basetypes.h"
#include "PCS_sys_types.h"

/* ----------------------------------------- */
/* constants normally defined in sys/mman.h */
/* ----------------------------------------- */

#define PCS_PROT_READ   0x1D21
#define PCS_PROT_WRITE  0x1D22
#define PCS_PROT_EXEC   0x1D23
#define PCS_PROT_NONE   0x1D24
#define PCS_MAP_SHARED  0x1D25
#define PCS_MAP_PRIVATE 0x1D26
#define PCS_MAP_FIXED   0x1D27

/* ----------------------------------------- */
/* types normally defined in sys/mman.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in sys/mman.h */
/* ----------------------------------------- */

extern void *PCS_mmap(void *addr, size_t len, int prot, int flags, int fildes, PCS_off_t off);

#endif
