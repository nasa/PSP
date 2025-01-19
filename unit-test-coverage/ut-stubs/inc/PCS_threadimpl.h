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

/* PSP coverage stub replacement for threadimpl.h */
#ifndef PCS_THREADIMPL_H
#define PCS_THREADIMPL_H

#include "PCS_rtems.h"

size_t PCS_Thread_Get_name(const PCS_Thread_Control *the_thread, char *buffer, size_t buffer_size);
PCS_Timestamp_Control PCS_Thread_Get_CPU_time_used_after_last_reset(PCS_Thread_Control *the_thread);

#endif