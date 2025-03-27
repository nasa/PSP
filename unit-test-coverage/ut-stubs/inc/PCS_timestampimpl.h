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

/* PSP coverage stub replacement for timestampimp.h */
#ifndef PCS_TIMESTAMPIMP_H
#define PCS_TIMESTAMPIMP_H

#include "PCS_rtems.h"

void PCS_Timestamp_Subtract (const PCS_Timestamp_Control *_start, const PCS_Timestamp_Control *_end, PCS_Timestamp_Control *_result);
void PCS_Timestamp_Divide (const PCS_Timestamp_Control *_lhs, const PCS_Timestamp_Control *_rhs, uint32_t *_ival_percentage, uint32_t *_fval_percentage);


#endif