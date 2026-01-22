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

/*
** Include Files
*/
#include "cfe_psp_endian_impl.h"

/* When compiled with _UNIT_TEST_, this changes the names of the functions
 * to allow multiple different implementations to be tested together */
#ifdef _UNIT_TEST_
#define PSP_ENDIAN_CONVERSION(f) ENDIAN_CONVERSION_COMBINE_NAME(UT_GENERIC, f)
#else
#define PSP_ENDIAN_CONVERSION(f) ENDIAN_CONVERSION_COMBINE_NAME(CFE_PSP, f)
#endif

union CFE_PSP_EndianWrap16
{
    uint16 Word;
    uint8  Octets[2];
};

union CFE_PSP_EndianWrap32
{
    uint32 Word;
    uint8  Octets[4];
};

union CFE_PSP_EndianWrap64
{
    uint64 Word;
    uint8  Octets[8];
};

/*
 * NOTE: the 16 bit conversions still use a 32 bit shift register.
 * This is intentional, on some architectures it adds an additional
 * (non-coverable) branch when shifting a short int
 */

uint16 PSP_ENDIAN_CONVERSION(HtoBE16)(uint16 host_16bits)
{
    union CFE_PSP_EndianWrap16 Out;
    uint32                     ShiftReg;
    size_t                     i;

    ShiftReg = host_16bits;
    Out.Word = 0;

    i = sizeof(Out);
    while (i > 0)
    {
        --i;
        Out.Octets[i] = ShiftReg & 0xFF;
        ShiftReg >>= 8;
    }

    return Out.Word;
}

uint16 PSP_ENDIAN_CONVERSION(HtoLE16)(uint16 host_16bits)
{
    union CFE_PSP_EndianWrap16 Out;
    uint32                     ShiftReg;
    size_t                     i;

    ShiftReg = host_16bits;
    Out.Word = 0;

    i = 0;
    while (i < sizeof(Out))
    {
        Out.Octets[i] = ShiftReg & 0xFF;
        ShiftReg >>= 8;
        ++i;
    }

    return Out.Word;
}

uint16 PSP_ENDIAN_CONVERSION(BE16toH)(uint16 big_endian_16bits)
{
    union CFE_PSP_EndianWrap16 In;
    uint32                     ShiftReg;
    size_t                     i;

    In.Word  = big_endian_16bits;
    ShiftReg = 0;

    i = 0;
    while (i < sizeof(In))
    {
        ShiftReg <<= 8;
        ShiftReg |= In.Octets[i];
        ++i;
    }

    return ShiftReg;
}

uint16 PSP_ENDIAN_CONVERSION(LE16toH)(uint16 little_endian_16bits)
{
    union CFE_PSP_EndianWrap16 In;
    uint32                     ShiftReg;
    size_t                     i;

    In.Word  = little_endian_16bits;
    ShiftReg = 0;

    i = sizeof(In);
    while (i > 0)
    {
        --i;
        ShiftReg <<= 8;
        ShiftReg |= In.Octets[i];
    }

    return ShiftReg;
}

uint32 PSP_ENDIAN_CONVERSION(HtoBE32)(uint32 host_32bits)
{
    union CFE_PSP_EndianWrap32 Out;
    uint32                     ShiftReg;
    size_t                     i;

    ShiftReg = host_32bits;
    Out.Word = 0;

    i = sizeof(Out);
    while (i > 0)
    {
        --i;
        Out.Octets[i] = ShiftReg & 0xFF;
        ShiftReg >>= 8;
    }

    return Out.Word;
}

uint32 PSP_ENDIAN_CONVERSION(HtoLE32)(uint32 host_32bits)
{
    union CFE_PSP_EndianWrap32 Out;
    uint32                     ShiftReg;
    size_t                     i;

    ShiftReg = host_32bits;
    Out.Word = 0;

    i = 0;
    while (i < sizeof(Out))
    {
        Out.Octets[i] = ShiftReg & 0xFF;
        ShiftReg >>= 8;
        ++i;
    }

    return Out.Word;
}

uint32 PSP_ENDIAN_CONVERSION(BE32toH)(uint32 big_endian_32bits)
{
    union CFE_PSP_EndianWrap32 In;
    uint32                     ShiftReg;
    size_t                     i;

    In.Word  = big_endian_32bits;
    ShiftReg = 0;

    i = 0;
    while (i < sizeof(In))
    {
        ShiftReg <<= 8;
        ShiftReg |= In.Octets[i];
        ++i;
    }

    return ShiftReg;
}

uint32 PSP_ENDIAN_CONVERSION(LE32toH)(uint32 little_endian_32bits)
{
    union CFE_PSP_EndianWrap32 In;
    uint32                     ShiftReg;
    size_t                     i;

    In.Word  = little_endian_32bits;
    ShiftReg = 0;

    i = sizeof(In);
    while (i > 0)
    {
        --i;
        ShiftReg <<= 8;
        ShiftReg |= In.Octets[i];
    }

    return ShiftReg;
}

uint64 PSP_ENDIAN_CONVERSION(HtoBE64)(uint64 host_64bits)
{
    union CFE_PSP_EndianWrap64 Out;
    uint64                     ShiftReg;
    size_t                     i;

    ShiftReg = host_64bits;
    Out.Word = 0;

    i = sizeof(Out);
    while (i > 0)
    {
        --i;
        Out.Octets[i] = ShiftReg & 0xFF;
        ShiftReg >>= 8;
    }

    return Out.Word;
}

uint64 PSP_ENDIAN_CONVERSION(HtoLE64)(uint64 host_64bits)
{
    union CFE_PSP_EndianWrap64 Out;
    uint64                     ShiftReg;
    size_t                     i;

    ShiftReg = host_64bits;
    Out.Word = 0;

    i = 0;
    while (i < sizeof(Out))
    {
        Out.Octets[i] = ShiftReg & 0xFF;
        ShiftReg >>= 8;
        ++i;
    }

    return Out.Word;
}

uint64 PSP_ENDIAN_CONVERSION(BE64toH)(uint64 big_endian_64bits)
{
    union CFE_PSP_EndianWrap64 In;
    uint64                     ShiftReg;
    size_t                     i;

    In.Word  = big_endian_64bits;
    ShiftReg = 0;

    i = 0;
    while (i < sizeof(In))
    {
        ShiftReg <<= 8;
        ShiftReg |= In.Octets[i];
        ++i;
    }

    return ShiftReg;
}

uint64 PSP_ENDIAN_CONVERSION(LE64toH)(uint64 little_endian_64bits)
{
    union CFE_PSP_EndianWrap64 In;
    uint64                     ShiftReg;
    size_t                     i;

    In.Word  = little_endian_64bits;
    ShiftReg = 0;

    i = sizeof(In);
    while (i > 0)
    {
        --i;
        ShiftReg <<= 8;
        ShiftReg |= In.Octets[i];
    }

    return ShiftReg;
}
