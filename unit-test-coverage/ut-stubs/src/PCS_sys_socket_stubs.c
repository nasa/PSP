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
 * Auto-Generated stub implementations for functions defined in PCS_sys_socket header
 */

#include "PCS_sys_socket.h"
#include "utgenstub.h"

void UT_DefaultHandler_PCS_recvfrom(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_accept()
 * ----------------------------------------------------
 */
int PCS_accept(int fd, struct PCS_sockaddr *addr, PCS_socklen_t *addr_len)
{
    UT_GenStub_SetupReturnBuffer(PCS_accept, int);

    UT_GenStub_AddParam(PCS_accept, int, fd);
    UT_GenStub_AddParam(PCS_accept, struct PCS_sockaddr *, addr);
    UT_GenStub_AddParam(PCS_accept, PCS_socklen_t *, addr_len);

    UT_GenStub_Execute(PCS_accept, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_accept, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_bind()
 * ----------------------------------------------------
 */
int PCS_bind(int fd, const struct PCS_sockaddr *addr, PCS_socklen_t len)
{
    UT_GenStub_SetupReturnBuffer(PCS_bind, int);

    UT_GenStub_AddParam(PCS_bind, int, fd);
    UT_GenStub_AddParam(PCS_bind, const struct PCS_sockaddr *, addr);
    UT_GenStub_AddParam(PCS_bind, PCS_socklen_t, len);

    UT_GenStub_Execute(PCS_bind, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_bind, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_connect()
 * ----------------------------------------------------
 */
int PCS_connect(int fd, const struct PCS_sockaddr *addr, PCS_socklen_t len)
{
    UT_GenStub_SetupReturnBuffer(PCS_connect, int);

    UT_GenStub_AddParam(PCS_connect, int, fd);
    UT_GenStub_AddParam(PCS_connect, const struct PCS_sockaddr *, addr);
    UT_GenStub_AddParam(PCS_connect, PCS_socklen_t, len);

    UT_GenStub_Execute(PCS_connect, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_connect, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_getsockopt()
 * ----------------------------------------------------
 */
int PCS_getsockopt(int fd, int level, int optname, void *optval, PCS_socklen_t *optlen)
{
    UT_GenStub_SetupReturnBuffer(PCS_getsockopt, int);

    UT_GenStub_AddParam(PCS_getsockopt, int, fd);
    UT_GenStub_AddParam(PCS_getsockopt, int, level);
    UT_GenStub_AddParam(PCS_getsockopt, int, optname);
    UT_GenStub_AddParam(PCS_getsockopt, void *, optval);
    UT_GenStub_AddParam(PCS_getsockopt, PCS_socklen_t *, optlen);

    UT_GenStub_Execute(PCS_getsockopt, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_getsockopt, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_listen()
 * ----------------------------------------------------
 */
int PCS_listen(int fd, int n)
{
    UT_GenStub_SetupReturnBuffer(PCS_listen, int);

    UT_GenStub_AddParam(PCS_listen, int, fd);
    UT_GenStub_AddParam(PCS_listen, int, n);

    UT_GenStub_Execute(PCS_listen, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_listen, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_recvfrom()
 * ----------------------------------------------------
 */
PCS_ssize_t PCS_recvfrom(int fd, void *buf, size_t n, int flags, struct PCS_sockaddr *addr, PCS_socklen_t *addr_len)
{
    UT_GenStub_SetupReturnBuffer(PCS_recvfrom, PCS_ssize_t);

    UT_GenStub_AddParam(PCS_recvfrom, int, fd);
    UT_GenStub_AddParam(PCS_recvfrom, void *, buf);
    UT_GenStub_AddParam(PCS_recvfrom, size_t, n);
    UT_GenStub_AddParam(PCS_recvfrom, int, flags);
    UT_GenStub_AddParam(PCS_recvfrom, struct PCS_sockaddr *, addr);
    UT_GenStub_AddParam(PCS_recvfrom, PCS_socklen_t *, addr_len);

    UT_GenStub_Execute(PCS_recvfrom, Basic, UT_DefaultHandler_PCS_recvfrom);

    return UT_GenStub_GetReturnValue(PCS_recvfrom, PCS_ssize_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_sendto()
 * ----------------------------------------------------
 */
PCS_ssize_t PCS_sendto(int fd, const void *buf, size_t n, int flags, const struct PCS_sockaddr *addr,
                       PCS_socklen_t addr_len)
{
    UT_GenStub_SetupReturnBuffer(PCS_sendto, PCS_ssize_t);

    UT_GenStub_AddParam(PCS_sendto, int, fd);
    UT_GenStub_AddParam(PCS_sendto, const void *, buf);
    UT_GenStub_AddParam(PCS_sendto, size_t, n);
    UT_GenStub_AddParam(PCS_sendto, int, flags);
    UT_GenStub_AddParam(PCS_sendto, const struct PCS_sockaddr *, addr);
    UT_GenStub_AddParam(PCS_sendto, PCS_socklen_t, addr_len);

    UT_GenStub_Execute(PCS_sendto, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_sendto, PCS_ssize_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_setsockopt()
 * ----------------------------------------------------
 */
int PCS_setsockopt(int fd, int level, int optname, const void *optval, PCS_socklen_t optlen)
{
    UT_GenStub_SetupReturnBuffer(PCS_setsockopt, int);

    UT_GenStub_AddParam(PCS_setsockopt, int, fd);
    UT_GenStub_AddParam(PCS_setsockopt, int, level);
    UT_GenStub_AddParam(PCS_setsockopt, int, optname);
    UT_GenStub_AddParam(PCS_setsockopt, const void *, optval);
    UT_GenStub_AddParam(PCS_setsockopt, PCS_socklen_t, optlen);

    UT_GenStub_Execute(PCS_setsockopt, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_setsockopt, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_shutdown()
 * ----------------------------------------------------
 */
int PCS_shutdown(int fd, int how)
{
    UT_GenStub_SetupReturnBuffer(PCS_shutdown, int);

    UT_GenStub_AddParam(PCS_shutdown, int, fd);
    UT_GenStub_AddParam(PCS_shutdown, int, how);

    UT_GenStub_Execute(PCS_shutdown, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_shutdown, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_socket()
 * ----------------------------------------------------
 */
int PCS_socket(int domain, int type, int protocol)
{
    UT_GenStub_SetupReturnBuffer(PCS_socket, int);

    UT_GenStub_AddParam(PCS_socket, int, domain);
    UT_GenStub_AddParam(PCS_socket, int, type);
    UT_GenStub_AddParam(PCS_socket, int, protocol);

    UT_GenStub_Execute(PCS_socket, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_socket, int);
}
