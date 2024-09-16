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

/************************************************************************
 * Note that this file has been cloned-n-owned from its open-source github
 * repository for Gateway as of September 2023. Therefore, it is subject to
 * NASA Export Control restrictions, as stated below.
 ************************************************************************/

/************************************************************************/
/** \export_control EAR ECCN 9E515.a and/or 9E515.f (HALO)
 *
 * Export Administration Regulations (EAR) Notice
 *
 * This document contains information which falls under the purview of the
 * Export Administration Regulations (EAR), 15 CFR §730-774 and is export
 * controlled. It may be used only to fulfill responsibilities of the Parties
 * of, or a Cooperating Agency of a NASA Gateway Program Partner (CSA, ESA,
 * JAXA, MBRSC) and their contractors in furtherance of the Gateway MOUs
 * with ESA, CSA, and Japan and IA with MBRSC. Any use, re-transfer, or
 * disclosure to any party for any purpose other than the designated use of
 * fulfilling the responsibilities of the Gateway MOUs and IA requires prior
 * U.S. Government authorization.
 *************************************************************************/

/**
 * \file
 * \ingroup ut-stubs
 *
 * OSAL coverage stub replacement for sys/socket.h
 */

#ifndef PCS_SYS_SOCKET_H
#define PCS_SYS_SOCKET_H

#include "PCS_basetypes.h"
#include "PCS_sys_types.h"
#include "PCS_netinet_in.h"

/* ----------------------------------------- */
/* constants normally defined in sys/socket.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in sys/socket.h */
/* ----------------------------------------- */
typedef size_t             PCS_socklen_t;
typedef unsigned short int PCS_sa_family_t;

struct PCS_sockaddr
{
    PCS_sa_family_t sa_family;
};

struct PCS_sockaddr_in
{
    PCS_sa_family_t    sin_family;
    uint16_t           sin_port;
    struct PCS_in_addr sin_addr;
};

struct PCS_sockaddr_in6
{
    PCS_sa_family_t sin6_family;
    uint16_t        sin6_port;
    uint32_t        sin6_addr[4];
};

enum
{
    PCS_IPPROTO_ICMP = 1,
    PCS_AF_INET,
    PCS_SOCK_RAW,
};

/* ----------------------------------------- */
/* prototypes normally declared in sys/socket.h */
/* ----------------------------------------- */

extern int         PCS_accept(int fd, struct PCS_sockaddr *addr, PCS_socklen_t *addr_len);
extern int         PCS_bind(int fd, const struct PCS_sockaddr *addr, PCS_socklen_t len);
extern int         PCS_connect(int fd, const struct PCS_sockaddr *addr, PCS_socklen_t len);
extern int         PCS_getsockopt(int fd, int level, int optname, void *optval, PCS_socklen_t *optlen);
extern int         PCS_listen(int fd, int n);
extern PCS_ssize_t PCS_recvfrom(int fd, void *buf, size_t n, int flags, struct PCS_sockaddr *addr,
                                PCS_socklen_t *addr_len);
extern PCS_ssize_t PCS_sendto(int fd, const void *buf, size_t n, int flags, const struct PCS_sockaddr *addr,
                              PCS_socklen_t addr_len);
extern int         PCS_setsockopt(int fd, int level, int optname, const void *optval, PCS_socklen_t optlen);
extern int         PCS_shutdown(int fd, int how);
extern int         PCS_socket(int domain, int type, int protocol);

#endif /* PCS_SYS_SOCKET_H */
