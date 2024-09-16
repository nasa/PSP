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
 * Auto-Generated stub implementations for functions defined in PCS_sys_select header
 */

#include "PCS_sys_select.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_FD_CLR()
 * ----------------------------------------------------
 */
void PCS_FD_CLR(int fd, PCS_fd_set *set)
{
    UT_GenStub_AddParam(PCS_FD_CLR, int, fd);
    UT_GenStub_AddParam(PCS_FD_CLR, PCS_fd_set *, set);

    UT_GenStub_Execute(PCS_FD_CLR, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_FD_ISSET()
 * ----------------------------------------------------
 */
int PCS_FD_ISSET(int fd, PCS_fd_set *set)
{
    UT_GenStub_SetupReturnBuffer(PCS_FD_ISSET, int);

    UT_GenStub_AddParam(PCS_FD_ISSET, int, fd);
    UT_GenStub_AddParam(PCS_FD_ISSET, PCS_fd_set *, set);

    UT_GenStub_Execute(PCS_FD_ISSET, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_FD_ISSET, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_FD_SET()
 * ----------------------------------------------------
 */
void PCS_FD_SET(int fd, PCS_fd_set *set)
{
    UT_GenStub_AddParam(PCS_FD_SET, int, fd);
    UT_GenStub_AddParam(PCS_FD_SET, PCS_fd_set *, set);

    UT_GenStub_Execute(PCS_FD_SET, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_FD_ZERO()
 * ----------------------------------------------------
 */
void PCS_FD_ZERO(PCS_fd_set *set)
{
    UT_GenStub_AddParam(PCS_FD_ZERO, PCS_fd_set *, set);

    UT_GenStub_Execute(PCS_FD_ZERO, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_select()
 * ----------------------------------------------------
 */
int PCS_select(int nfds, PCS_fd_set *readfds, PCS_fd_set *writefds, PCS_fd_set *exceptfds, struct PCS_timeval *timeout)
{
    UT_GenStub_SetupReturnBuffer(PCS_select, int);

    UT_GenStub_AddParam(PCS_select, int, nfds);
    UT_GenStub_AddParam(PCS_select, PCS_fd_set *, readfds);
    UT_GenStub_AddParam(PCS_select, PCS_fd_set *, writefds);
    UT_GenStub_AddParam(PCS_select, PCS_fd_set *, exceptfds);
    UT_GenStub_AddParam(PCS_select, struct PCS_timeval *, timeout);

    UT_GenStub_Execute(PCS_select, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_select, int);
}
