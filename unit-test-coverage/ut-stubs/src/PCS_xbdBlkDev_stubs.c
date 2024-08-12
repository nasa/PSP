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

/**
 * @file
 *
 * Auto-Generated stub implementations for functions defined in PCS_xbdBlkDev header
 */

#include "PCS_xbdBlkDev.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_xbdBlkDevCreateSync()
 * ----------------------------------------------------
 */
PCS_device_t PCS_xbdBlkDevCreateSync(PCS_BLK_DEV *bd, const char *name)
{
    UT_GenStub_SetupReturnBuffer(PCS_xbdBlkDevCreateSync, PCS_device_t);

    UT_GenStub_AddParam(PCS_xbdBlkDevCreateSync, PCS_BLK_DEV *, bd);
    UT_GenStub_AddParam(PCS_xbdBlkDevCreateSync, const char *, name);

    UT_GenStub_Execute(PCS_xbdBlkDevCreateSync, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_xbdBlkDevCreateSync, PCS_device_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_xbdBlkDevDelete()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_xbdBlkDevDelete(PCS_device_t dev, PCS_BLK_DEV **ppbd)
{
    UT_GenStub_SetupReturnBuffer(PCS_xbdBlkDevDelete, PCS_STATUS);

    UT_GenStub_AddParam(PCS_xbdBlkDevDelete, PCS_device_t, dev);
    UT_GenStub_AddParam(PCS_xbdBlkDevDelete, PCS_BLK_DEV **, ppbd);

    UT_GenStub_Execute(PCS_xbdBlkDevDelete, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_xbdBlkDevDelete, PCS_STATUS);
}
