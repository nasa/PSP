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

/* PSP coverage stub replacement for time.h */
#ifndef PCS_TIME_H
#define PCS_TIME_H

#include "PCS_basetypes.h"

/* ----------------------------------------- */
/* constants normally defined in time.h */
/* ----------------------------------------- */
#define PCS_CLOCK_REALTIME  0x0 /* system wide realtime clock */
#define PCS_CLOCK_MONOTONIC 0x1 /* system wide monotonic clock */

/* ----------------------------------------- */
/* types normally defined in time.h */
/* ----------------------------------------- */
typedef long PCS_time_t;
typedef long PCS_suseconds_t;

struct PCS_timespec
{
    PCS_time_t tv_sec;
    long       tv_nsec;
};

/* ----------------------------------------- */
/* prototypes normally declared in time.h */
/* ----------------------------------------- */
int PCS_clock_settime(int clk_id, struct PCS_timespec *t);
int PCS_clock_gettime(int clk_id, struct PCS_timespec *t);

#endif
