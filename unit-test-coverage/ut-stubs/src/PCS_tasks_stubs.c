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
 * Auto-Generated stub implementations for functions defined in PCS_tasks header
 */

#include "PCS_tasks.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_rtems_task_create()
 * ----------------------------------------------------
 */
PCS_rtems_status_code PCS_rtems_task_create(PCS_rtems_name name, PCS_rtems_task_priority initial_priority,
                                            size_t stack_size, PCS_rtems_mode initial_modes,
                                            PCS_rtems_attribute attribute_set, PCS_rtems_id *id)
{
    UT_GenStub_SetupReturnBuffer(PCS_rtems_task_create, PCS_rtems_status_code);

    UT_GenStub_AddParam(PCS_rtems_task_create, PCS_rtems_name, name);
    UT_GenStub_AddParam(PCS_rtems_task_create, PCS_rtems_task_priority, initial_priority);
    UT_GenStub_AddParam(PCS_rtems_task_create, size_t, stack_size);
    UT_GenStub_AddParam(PCS_rtems_task_create, PCS_rtems_mode, initial_modes);
    UT_GenStub_AddParam(PCS_rtems_task_create, PCS_rtems_attribute, attribute_set);
    UT_GenStub_AddParam(PCS_rtems_task_create, PCS_rtems_id *, id);

    UT_GenStub_Execute(PCS_rtems_task_create, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_rtems_task_create, PCS_rtems_status_code);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_rtems_task_delete()
 * ----------------------------------------------------
 */
PCS_rtems_status_code PCS_rtems_task_delete(PCS_rtems_id id)
{
    UT_GenStub_SetupReturnBuffer(PCS_rtems_task_delete, PCS_rtems_status_code);

    UT_GenStub_AddParam(PCS_rtems_task_delete, PCS_rtems_id, id);

    UT_GenStub_Execute(PCS_rtems_task_delete, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_rtems_task_delete, PCS_rtems_status_code);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_rtems_task_iterate()
 * ----------------------------------------------------
 */
void PCS_rtems_task_iterate(PCS_rtems_task_visitor visitor, void *arg)
{
    UT_GenStub_AddParam(PCS_rtems_task_iterate, PCS_rtems_task_visitor, visitor);
    UT_GenStub_AddParam(PCS_rtems_task_iterate, void *, arg);

    UT_GenStub_Execute(PCS_rtems_task_iterate, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_rtems_task_start()
 * ----------------------------------------------------
 */
PCS_rtems_status_code PCS_rtems_task_start(PCS_rtems_id id, PCS_rtems_task_entry entry_point,
                                           PCS_rtems_task_argument argument)
{
    UT_GenStub_SetupReturnBuffer(PCS_rtems_task_start, PCS_rtems_status_code);

    UT_GenStub_AddParam(PCS_rtems_task_start, PCS_rtems_id, id);
    UT_GenStub_AddParam(PCS_rtems_task_start, PCS_rtems_task_entry, entry_point);
    UT_GenStub_AddParam(PCS_rtems_task_start, PCS_rtems_task_argument, argument);

    UT_GenStub_Execute(PCS_rtems_task_start, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_rtems_task_start, PCS_rtems_status_code);
}
