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
#ifndef OVERRIDE_RTEMS_H
#define OVERRIDE_RTEMS_H

#include "PCS_rtems.h"

#define rtems_task_priority PCS_rtems_task_priority
#define rtems_id            PCS_rtems_id

#define rtems_status_code PCS_rtems_status_code
#define RTEMS_SUCCESSFUL  PCS_RTEMS_SUCCESSFUL

#define rtems_bsdnet_ifconfig PCS_rtems_bsdnet_ifconfig
#define rtems_bsdnet_config   PCS_rtems_bsdnet_config

#endif
