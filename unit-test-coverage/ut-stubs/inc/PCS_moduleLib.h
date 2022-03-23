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

/* PSP coverage stub replacement for moduleLib.h */
#ifndef PCS_MODULELIB_H
#define PCS_MODULELIB_H

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"

/* ----------------------------------------- */
/* constants normally defined in moduleLib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in moduleLib.h */
/* ----------------------------------------- */
typedef struct PCS_MODULE
{
    int m;
} PCS_MODULE;
typedef PCS_MODULE *PCS_MODULE_ID;

typedef struct PCS_MODULE_INFO
{
    struct
    {
        unsigned long textAddr;
        unsigned long textSize;
        unsigned long dataAddr;
        unsigned long dataSize;
        unsigned long bssAddr;
        unsigned long bssSize;
    } segInfo;

} PCS_MODULE_INFO;

/* ----------------------------------------- */
/* prototypes normally declared in moduleLib.h */
/* ----------------------------------------- */

extern PCS_STATUS    PCS_moduleInfoGet(PCS_MODULE_ID moduleId, PCS_MODULE_INFO *pModuleInfo);
extern PCS_MODULE_ID PCS_moduleFindByName(const char *moduleName);

#endif
