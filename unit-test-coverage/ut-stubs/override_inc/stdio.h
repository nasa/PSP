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

/* PSP coverage stub replacement for stdio.h */
#ifndef OVERRIDE_STDIO_H
#define OVERRIDE_STDIO_H

#include "PCS_stdio.h"

/* ----------------------------------------- */
/* mappings for declarations in stdio.h */
/* ----------------------------------------- */

#define FILE        PCS_FILE
#define fclose      PCS_fclose
#define fgets       PCS_fgets
#define fopen       PCS_fopen
#define fputs       PCS_fputs
#define remove      PCS_remove
#define rename      PCS_rename
#define snprintf    PCS_snprintf
#define vsnprintf   PCS_vsnprintf
#define printf(...) PCS_printf(__VA_ARGS__)
#define putchar     PCS_putchar
#define perror      PCS_perror

#define stdin  PCS_stdin
#define stdout PCS_stdout
#define stderr PCS_stderr

#endif
