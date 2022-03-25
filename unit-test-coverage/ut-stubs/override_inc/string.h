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
#ifndef OVERRIDE_STRING_H
#define OVERRIDE_STRING_H

#include "PCS_string.h"

/* ----------------------------------------- */
/* mappings for declarations in string.h */
/* ----------------------------------------- */
#define memcpy   PCS_memcpy
#define memset   PCS_memset
#define strcmp   PCS_strcmp
#define strcpy   PCS_strcpy
#define strlen   PCS_strlen
#define strncmp  PCS_strncmp
#define strncpy  PCS_strncpy
#define strchr   PCS_strchr
#define strrchr  PCS_strrchr
#define strcat   PCS_strcat
#define strncat  PCS_strncat
#define strerror PCS_strerror

#endif
