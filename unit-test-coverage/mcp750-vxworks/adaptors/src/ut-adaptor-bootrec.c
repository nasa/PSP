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
 * \file
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
