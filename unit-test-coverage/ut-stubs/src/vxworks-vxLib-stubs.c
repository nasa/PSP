/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for vxLib.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_vxLib.h"
#include "PCS_arch_ppc_vxPpcLib.h"

void PCS_vxTimeBaseGet(uint32_t *u, uint32_t *l)
{
    UT_Stub_RegisterContextGenericArg(UT_KEY(PCS_vxTimeBaseGet), u);
    UT_Stub_RegisterContextGenericArg(UT_KEY(PCS_vxTimeBaseGet), l);
    *u = 0;
    *l = 0;
    UT_DEFAULT_IMPL(PCS_vxTimeBaseGet);
}
void PCS_vxMsrSet(uint32_t val)
{
    UT_DEFAULT_IMPL(PCS_vxMsrSet);
}
uint32_t PCS_vxMsrGet(void)
{
    return UT_DEFAULT_IMPL(PCS_vxMsrGet);
}
void PCS_vxFpscrSet(uint32_t val)
{
    UT_DEFAULT_IMPL(PCS_vxFpscrSet);
}
uint32_t PCS_vxFpscrGet(void)
{
    return UT_DEFAULT_IMPL(PCS_vxFpscrGet);
}
uint32_t PCS_vxDecGet(void)
{
    return UT_DEFAULT_IMPL(PCS_vxDecGet);
}
