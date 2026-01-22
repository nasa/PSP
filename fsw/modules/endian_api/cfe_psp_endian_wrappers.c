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
 * When compiled with optimization enabled, these should generally get reduced
 * to just a couple instructions (e.g. bswap)
 */

/*
** Include Files
*/
#include <endian.h>
#include "cfe_psp_endian_impl.h"

/* When compiled with _UNIT_TEST_, this changes the names of the functions
 * to allow multiple different implementations to be tested together */
#ifdef _UNIT_TEST_
#define PSP_ENDIAN_CONVERSION(f) ENDIAN_CONVERSION_COMBINE_NAME(UT_WRAPPED, f)
#else
#define PSP_ENDIAN_CONVERSION(f) ENDIAN_CONVERSION_COMBINE_NAME(CFE_PSP, f)
#endif

uint16 PSP_ENDIAN_CONVERSION(HtoBE16)(uint16 host_16bits)
{
    return htobe16(host_16bits);
}

uint16 PSP_ENDIAN_CONVERSION(HtoLE16)(uint16 host_16bits)
{
    return htole16(host_16bits);
}

uint16 PSP_ENDIAN_CONVERSION(BE16toH)(uint16 big_endian_16bits)
{
    return be16toh(big_endian_16bits);
}

uint16 PSP_ENDIAN_CONVERSION(LE16toH)(uint16 little_endian_16bits)
{
    return le16toh(little_endian_16bits);
}

uint32 PSP_ENDIAN_CONVERSION(HtoBE32)(uint32 host_32bits)
{
    return htobe32(host_32bits);
}

uint32 PSP_ENDIAN_CONVERSION(HtoLE32)(uint32 host_32bits)
{
    return htole32(host_32bits);
}

uint32 PSP_ENDIAN_CONVERSION(BE32toH)(uint32 big_endian_32bits)
{
    return be32toh(big_endian_32bits);
}

uint32 PSP_ENDIAN_CONVERSION(LE32toH)(uint32 little_endian_32bits)
{
    return le32toh(little_endian_32bits);
}

uint64 PSP_ENDIAN_CONVERSION(HtoBE64)(uint64 host_64bits)
{
    return htobe64(host_64bits);
}

uint64 PSP_ENDIAN_CONVERSION(HtoLE64)(uint64 host_64bits)
{
    return htole64(host_64bits);
}

uint64 PSP_ENDIAN_CONVERSION(BE64toH)(uint64 big_endian_64bits)
{
    return be64toh(big_endian_64bits);
}

uint64 PSP_ENDIAN_CONVERSION(LE64toH)(uint64 little_endian_64bits)
{
    return le64toh(little_endian_64bits);
}
