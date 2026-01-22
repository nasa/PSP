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

#ifndef CFE_PSP_ENDIAN_H
#define CFE_PSP_ENDIAN_H

/*
** Include Files
*/
#include "common_types.h"

uint16 CFE_PSP_HtoBE16(uint16 host_16bits);
uint16 CFE_PSP_HtoLE16(uint16 host_16bits);
uint16 CFE_PSP_BE16toH(uint16 big_endian_16bits);
uint16 CFE_PSP_LE16toH(uint16 little_endian_16bits);

uint32 CFE_PSP_HtoBE32(uint32 host_32bits);
uint32 CFE_PSP_HtoLE32(uint32 host_32bits);
uint32 CFE_PSP_BE32toH(uint32 big_endian_32bits);
uint32 CFE_PSP_LE32toH(uint32 little_endian_32bits);

uint64 CFE_PSP_HtoBE64(uint64 host_64bits);
uint64 CFE_PSP_HtoLE64(uint64 host_64bits);
uint64 CFE_PSP_BE64toH(uint64 big_endian_64bits);
uint64 CFE_PSP_LE64toH(uint64 little_endian_64bits);

bool CFE_PSP_IsBigEndian(void);
bool CFE_PSP_IsLittleEndian(void);

#endif /* CFE_PSP_ENDIAN_H */
