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

/* PSP coverage stub replacement for userReservedMem.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_sys_socket.h"

void UT_DefaultHandler_PCS_recvfrom(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* PCS_ssize_t PCS_recvfrom(int fd, void *buf, size_t n, int flags, struct PCS_sockaddr *addr, PCS_socklen_t
     * *addr_len) */
    void * buf = UT_Hook_GetArgValueByName(Context, "buf", void *);
    size_t n   = UT_Hook_GetArgValueByName(Context, "n", size_t);
    int32  iStatus;

    UT_Stub_GetInt32StatusCode(Context, &iStatus);

    if (iStatus >= 0)
    {
        if (n > iStatus)
        {
            n = iStatus;
        }

        UT_Stub_CopyToLocal(UT_KEY(PCS_recvfrom), buf, n);
    }
}
