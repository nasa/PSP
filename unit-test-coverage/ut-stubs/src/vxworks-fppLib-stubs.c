/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for fppLib.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_fppLib.h"

void PCS_fppSave(PCS_FP_CONTEXT *fpc)
{
    UT_DEFAULT_IMPL(PCS_fppSave);
}
