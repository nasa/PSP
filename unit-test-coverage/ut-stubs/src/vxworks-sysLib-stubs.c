/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for sysLib.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_sysLib.h"

int PCS_sysClkRateGet(void)
{
    return (UT_DEFAULT_IMPL_RC(PCS_sysClkRateGet, 10000));
}
char *PCS_sysMemTop(void)
{
    int32 Status;
    char *BufPtr;

    BufPtr = NULL;
    Status = UT_DEFAULT_IMPL(PCS_sysMemTop);
    if (Status == 0)
    {
        UT_GetDataBuffer(UT_KEY(PCS_sysMemTop), (void **)&BufPtr, NULL, NULL);
    }

    return BufPtr;
}

void PCS_PciOutByte(uint32_t address, uint8_t data)
{
    UT_DEFAULT_IMPL(PCS_PciOutByte);
}
void PCS_PciOutLong(uint32_t address, uint32_t data)
{
    UT_DEFAULT_IMPL(PCS_PciOutLong);
}
void PCS_sysPciWrite32(uint32_t address, uint32_t data)
{
    UT_DEFAULT_IMPL(PCS_sysPciWrite32);
}
void PCS_sysPciRead32(uint32_t address, uint32_t *data)
{
    UT_DEFAULT_IMPL(PCS_sysPciRead32);
}

unsigned int PCS_GetWrsKernelTextStart(void)
{
    return (UT_DEFAULT_IMPL(PCS_GetWrsKernelTextStart));
}

unsigned int PCS_GetWrsKernelTextEnd(void)
{
    return (UT_DEFAULT_IMPL(PCS_GetWrsKernelTextEnd));
}
