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
#ifndef PCS_STDIO_H
#define PCS_STDIO_H

#include "PCS_basetypes.h"
#include "PCS_stdarg.h"

/* ----------------------------------------- */
/* constants normally defined in stdio.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in stdio.h */
/* ----------------------------------------- */
typedef struct PCS_FILE PCS_FILE;

/* ----------------------------------------- */
/* prototypes normally declared in stdio.h */
/* ----------------------------------------- */

extern int       PCS_fclose(PCS_FILE *stream);
extern char *    PCS_fgets(char *s, int n, PCS_FILE *stream);
extern PCS_FILE *PCS_fopen(const char *filename, const char *modes);
extern int       PCS_fputs(const char *s, PCS_FILE *stream);
extern int       PCS_remove(const char *filename);
extern int       PCS_rename(const char *old, const char *nw);
extern int       PCS_snprintf(char *s, size_t maxlen, const char *format, ...);
extern int       PCS_vsnprintf(char *s, size_t maxlen, const char *format, PCS_va_list arg);
extern int       PCS_printf(const char *format, ...);
extern int       PCS_putchar(int c);

extern PCS_FILE *PCS_stdin;
extern PCS_FILE *PCS_stdout;
extern PCS_FILE *PCS_stderr;

#endif
