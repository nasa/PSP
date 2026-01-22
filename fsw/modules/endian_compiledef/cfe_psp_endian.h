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
 * Purpose:
 *      Define macros to enforce big-endian/network byte order for 16 and 32 bit integers
 *
 */

#ifndef CFE_PSP_ENDIAN_H
#define CFE_PSP_ENDIAN_H

/*
** Include Files
*/
#include <endian.h>
#include "common_types.h"

static inline uint16 CFE_PSP_htobe16(uint16 host_16bits)
{
    return htobe16(host_16bits);
}

static inline uint16 CFE_PSP_htole16(uint16 host_16bits)
{
    return htole16(host_16bits);
}

static inline uint16 CFE_PSP_be16toh(uint16 big_endian_16bits)
{
    return be16toh(big_endian_16bits);
}

static inline uint16 CFE_PSP_le16toh(uint16 little_endian_16bits)
{
    return le16toh(little_endian_16bits);
}

static inline uint32 CFE_PSP_htobe32(uint32 host_32bits)
{
    return htobe32(host_32bits);
}

static inline uint32 CFE_PSP_htole32(uint32 host_32bits)
{
    return htole32(host_32bits);
}

static inline uint32 CFE_PSP_be32toh(uint32 big_endian_32bits)
{
    return be32toh(big_endian_32bits);
}

static inline uint32 CFE_PSP_le32toh(uint32 little_endian_32bits)
{
    return le32toh(little_endian_32bits);
}

static inline uint64 CFE_PSP_htobe64(uint64 host_64bits)
{
    return htobe64(host_64bits);
}

static inline uint64 CFE_PSP_htole64(uint64 host_64bits)
{
    return htole64(host_64bits);
}

static inline uint64 CFE_PSP_be64toh(uint64 big_endian_64bits)
{
    return be64toh(big_endian_64bits);
}

static inline uint64 CFE_PSP_le64toh(uint64 little_endian_64bits)
{
    return le64toh(little_endian_64bits);
}

#endif /* CFE_PSP_ENDIAN_H */
