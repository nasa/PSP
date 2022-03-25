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

/* PSP coverage stub replacement for stdlib.h */
#ifndef PCS_STDLIB_H
#define PCS_STDLIB_H

#include "PCS_basetypes.h"

/* ----------------------------------------- */
/* constants normally defined in stdlib.h */
/* ----------------------------------------- */

#define PCS_EXIT_SUCCESS 0x0100
#define PCS_EXIT_FAILURE 0x0101

/* ----------------------------------------- */
/* types normally defined in stdlib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in stdlib.h */
/* ----------------------------------------- */

extern void              PCS_exit(int status);
extern unsigned long int PCS_strtoul(const char *nptr, char **endptr, int base);
extern int               PCS_system(const char *command);
extern void *            PCS_malloc(size_t sz);
extern void              PCS_free(void *ptr);

#endif
