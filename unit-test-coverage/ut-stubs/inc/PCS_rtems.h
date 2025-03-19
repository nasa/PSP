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

/* PSP coverage stub replacement for rtems.h */
#ifndef PCS_RTEMS_H
#define PCS_RTEMS_H

#include "PCS_basetypes.h"

#define PCS_RTEMS_SELF               0
#define PCS_RTEMS_DEFAULT_MODES      0x00000000
#define PCS_RTEMS_DEFAULT_ATTRIBUTES 0x00000000

typedef uint32_t          PCS_rtems_task_priority;
typedef uint32_t          PCS_rtems_id;
typedef uint32_t          PCS_rtems_name;
typedef uintptr_t         PCS_CPU_Uint32ptr;
typedef int64_t           PCS_Timestamp_Control;
typedef void              PCS_rtems_task;
typedef uint32_t          PCS_rtems_mode;
typedef uint32_t          PCS_rtems_attribute;
typedef PCS_CPU_Uint32ptr PCS_rtems_task_argument;

typedef struct {
    /* Fake Thread control  */
    char * Name;
} PCS_Thread_Control_S;

typedef PCS_Thread_Control_S PCS_rtems_tcb;
typedef PCS_rtems_tcb        PCS_Thread_Control;

struct PCS_rtems_bsdnet_ifconfig
{
    char *name;
    int (*attach)(struct PCS_rtems_bsdnet_ifconfig *conf, int attaching);
    struct PCS_rtems_bsdnet_ifconfig *next;
    char *                            ip_address;
    char *                            ip_netmask;
    void *                            hardware_address;
};

struct PCS_rtems_bsdnet_config
{
    struct PCS_rtems_bsdnet_ifconfig *ifconfig;
    void (*bootp)(void);
};

typedef enum
{
    PCS_RTEMS_SUCCESSFUL = 0,
} PCS_rtems_status_code;

#endif
