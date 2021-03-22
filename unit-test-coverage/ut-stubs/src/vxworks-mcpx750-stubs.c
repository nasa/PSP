/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for memPartLib.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_mcpx750.h"

static uint32_t PCS_SYS_REG_BLRR_VALUE;

uint32_t *PCS_SYS_REG_BLRR = &PCS_SYS_REG_BLRR_VALUE;
