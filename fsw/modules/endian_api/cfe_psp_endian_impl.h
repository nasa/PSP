/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
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

/**
 * @file
 *
 * Map the PSP endian conversion routines to the system-provided endian.h file
 * This is done using static inline functions, such that the result should be
 * optimized as much as possible.
 */

#ifndef CFE_PSP_ENDIAN_IMPL_H
#define CFE_PSP_ENDIAN_IMPL_H

/*
** Include Files
*/
#include "cfe_psp_endian.h"

#define ENDIAN_CONVERSION_COMBINE_NAME(ns, f) ns##_##f

#endif
