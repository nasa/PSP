/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for moduleLib.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_moduleLib.h"

PCS_MODULE_ID PCS_moduleFindByName(const char *moduleName)
{
    PCS_MODULE_ID retval;
    int32         Status;

    retval = NULL;
    Status = UT_DEFAULT_IMPL(PCS_moduleFindByName);
    if (Status == 0)
    {
        UT_Stub_CopyToLocal(UT_KEY(PCS_moduleFindByName), &retval, sizeof(retval));
    }

    return retval;
}

PCS_STATUS PCS_moduleInfoGet(PCS_MODULE_ID moduleId, PCS_MODULE_INFO *pModuleInfo)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_moduleInfoGet);

    if (Status == 0 &&
        UT_Stub_CopyToLocal(UT_KEY(PCS_moduleInfoGet), pModuleInfo, sizeof(*pModuleInfo)) < sizeof(*pModuleInfo))
    {
        memset(pModuleInfo, 0, sizeof(*pModuleInfo));
    }

    return Status;
}
