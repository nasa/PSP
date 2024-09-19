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

#ifndef OVERRIDE_SYS_SOCKET_H
#define OVERRIDE_SYS_SOCKET_H

#include "PCS_sys_socket.h"

/* ----------------------------------------- */
/* mappings for declarations in sys/socket.h */
/* ----------------------------------------- */
#define socklen_t    PCS_socklen_t
#define sockaddr     PCS_sockaddr
#define sockaddr_in  PCS_sockaddr_in
#define sockaddr_in6 PCS_sockaddr_in6
#define sa_family_t  PCS_sa_family_t
#define accept       PCS_accept
#define bind         PCS_bind
#define connect      PCS_connect
#define getsockopt   PCS_getsockopt
#define listen       PCS_listen
#define recvfrom     PCS_recvfrom
#define sendto       PCS_sendto
#define setsockopt   PCS_setsockopt
#define shutdown     PCS_shutdown
#define socket       PCS_socket

#define IPPROTO_ICMP PCS_IPPROTO_ICMP
#define AF_INET      PCS_AF_INET
#define SOCK_RAW     PCS_SOCK_RAW

#endif /* OVERRIDE_SYS_SOCKET_H */
