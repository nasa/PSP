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

/* PSP coverage stub replacement for string.h */
#ifndef PCS_STRING_H
#define PCS_STRING_H

#include "PCS_basetypes.h"

/* ----------------------------------------- */
/* constants normally defined in string.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in string.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in string.h */
/* ----------------------------------------- */

extern void * PCS_memcpy(void *dest, const void *src, size_t n);
extern void * PCS_memset(void *s, int c, size_t n);
extern int    PCS_strcmp(const char *s1, const char *s2);
extern char * PCS_strcpy(char *dest, const char *src);
extern size_t PCS_strlen(const char *s);
extern int    PCS_strncmp(const char *s1, const char *s2, size_t n);
extern char * PCS_strncpy(char *dest, const char *src, size_t n);
extern char * PCS_strchr(const char *s, int c);
extern char * PCS_strrchr(const char *s, int c);
extern char * PCS_strcat(char *dest, const char *src);
extern char * PCS_strncat(char *dest, const char *src, size_t n);
extern char * PCS_strerror(int errnum);

#endif
