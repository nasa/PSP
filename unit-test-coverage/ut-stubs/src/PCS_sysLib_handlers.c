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

/* PSP coverage stub replacement for sysLib.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_sysLib.h"

void UT_DefaultHandler_PCS_sysClkRateGet(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int PCS_sysClkRateGet(void) */
    int DefaultValue = 10000;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        UT_Stub_SetReturnValue(FuncKey, DefaultValue);
    }
}

void UT_DefaultHandler_PCS_sysMemTop(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* char *PCS_sysMemTop(void) */
    int32 Status;
    char *BufPtr;

    BufPtr = NULL;
    UT_Stub_GetInt32StatusCode(Context, &Status);
    if (Status == 0)
    {
        UT_GetDataBuffer(UT_KEY(PCS_sysMemTop), (void **)&BufPtr, NULL, NULL);
        if (BufPtr != NULL)
        {
            UT_Stub_SetReturnValue(FuncKey, BufPtr);
        }
    }
}

void UT_DefaultHandler_PCS_sysPhysMemTop(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* char *PCS_sysPhysMemTop(void) */
    int32 Status;
    void *BufPtr;

    BufPtr = NULL;
    UT_Stub_GetInt32StatusCode(Context, &Status);
    if (Status == 0)
    {
        UT_Stub_CopyToLocal(UT_KEY(PCS_sysPhysMemTop), &BufPtr, sizeof(BufPtr));
        UT_Stub_SetReturnValue(FuncKey, BufPtr);
    }
}
