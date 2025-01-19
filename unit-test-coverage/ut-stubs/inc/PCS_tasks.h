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

/* PSP coverage stub replacement for tasks.h */
#ifndef PCS_TASKS_H
#define PCS_TASKS_H

#include "PCS_rtems.h"

typedef bool( * PCS_rtems_task_visitor) (PCS_rtems_tcb *tcb, void *arg);
typedef PCS_rtems_task( * PCS_rtems_task_entry) (PCS_rtems_task_argument);

void PCS_rtems_task_iterate (PCS_rtems_task_visitor visitor, void *arg);
PCS_rtems_status_code PCS_rtems_task_delete (PCS_rtems_id id);
PCS_rtems_status_code PCS_rtems_task_create (PCS_rtems_name name, PCS_rtems_task_priority initial_priority, size_t stack_size, 
                                             PCS_rtems_mode initial_modes, PCS_rtems_attribute attribute_set, PCS_rtems_id *id);
PCS_rtems_status_code PCS_rtems_task_start (PCS_rtems_id id, PCS_rtems_task_entry entry_point, PCS_rtems_task_argument argument);



#endif