/*
 *
 *    Copyright (c) 2020, United States government as represented by the
 *    administrator of the National Aeronautics Space Administration.
 *    All rights reserved. This software was created at NASA Goddard
 *    Space Flight Center pursuant to government contracts.
 *
 *    This is governed by the NASA Open Source Agreement and may be used,
 *    distributed and modified only according to the terms of that agreement.
 *
 */

/**
 * \file     ut-adaptor-bootrec.c
 * \ingroup  adaptors
 * \author   joseph.p.hickey@nasa.gov
 *
 */

#include "ut-adaptor-bootrec.h"
#include "cfe_psp_config.h"
#include "cfe_psp_memory.h"

static CFE_PSP_ReservedMemoryBootRecord_t UT_BOOTREC;

static const CFE_PSP_ReservedMemoryBootRecord_t UT_DEFAULT_BOOTREC = {0};

void UT_Setup_ReservedMem_BootRec(void)
{
    UT_BOOTREC                        = UT_DEFAULT_BOOTREC;
    CFE_PSP_ReservedMemoryMap.BootPtr = &UT_BOOTREC;
}

uint32 UT_Get_ReservedMem_BootType(void)
{
    return UT_BOOTREC.bsp_reset_type;
}

void UT_Set_ReservedMem_BootType(uint32 reset_type)
{
    UT_BOOTREC.bsp_reset_type = reset_type;
}
