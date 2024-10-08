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

/* PSP coverage stub replacement for arpa/inet.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_arpa_inet.h"

#define MAX_NTOA_LEN 64

void UT_DefaultHandler_PCS_inet_addr(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint32 PCS_inet_addr(const char *cp) */
    uint32 *pAddr = NULL;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        UT_GetDataBuffer(FuncKey, (void **)&pAddr, NULL, NULL);
        if (pAddr != NULL)
        {
            UT_Stub_SetReturnValue(FuncKey, *pAddr);
        }
    }
}

void UT_DefaultHandler_PCS_inet_ntoa(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* char *PCS_inet_ntoa(struct PCS_in_addr in) */
    static char Buf[MAX_NTOA_LEN] = "";
    char *      pBuf              = Buf;

    if (!UT_Stub_GetInt32StatusCode(Context, NULL))
    {
        UT_Stub_CopyToLocal(FuncKey, pBuf, sizeof(Buf));
        UT_Stub_SetReturnValue(FuncKey, pBuf);
    }
}
