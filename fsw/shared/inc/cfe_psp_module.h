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
 * \file
 *
 * PSP Module Header
 */

#ifndef CFE_PSP_MODULE_H
#define CFE_PSP_MODULE_H

#include "cfe_psp.h"
#include "target_config.h"

/**
 * \brief Combines the basic information about a module list
 *
 * This is the info typically needed when finding a module
 *  - pointer to first module
 *  - length of list
 *  - "id" space used for list (base value)
 */
typedef struct CFE_PSP_ModuleListWrapper
{
    CFE_StaticModuleLoadEntry_t *BasePtr;
    uint32                       ListLen;
    uint32                       BaseId;
} CFE_PSP_ModuleListWrapper_t;

/**
 * \brief Combines the fixed and user-selected module lists
 *
 * This allows the complete set of modules to be expressed
 * in a single structure
 */
typedef struct CFE_PSP_ModuleListGlobal
{
    /** The "Std" list has the basic set of modules that must always be present */
    CFE_PSP_ModuleListWrapper_t Std;

    /** The "Ext" list has any additional optional modules that the user has selected */
    CFE_PSP_ModuleListWrapper_t Ext;

} CFE_PSP_ModuleListGlobal_t;

/**
 ** \brief Enum Module Type
 ** May be extended in the future
 */
typedef enum
{
    CFE_PSP_MODULE_TYPE_INVALID = 0,
    CFE_PSP_MODULE_TYPE_SIMPLE,
    CFE_PSP_MODULE_TYPE_DEVICEDRIVER,
    /* May be extended in the future */
} CFE_PSP_ModuleType_t;

/**
 * Prototype for a PSP module initialization function
 */
typedef void (*CFE_PSP_ModuleInitFunc_t)(uint32 PspModuleId);

/**
 * Concrete version of the abstract API definition structure
 */
typedef const struct
{
    CFE_PSP_ModuleType_t     ModuleType;
    uint32                   OperationFlags;
    CFE_PSP_ModuleInitFunc_t Init;
    /* More API calls may be added for other module types */
    const void *ExtendedApi;
} CFE_PSP_ModuleApi_t;

/**
 * Macro to simplify declaration of the IO Driver API structure
 * according to the required naming convention.
 *
 * The "name" argument should match the name of the module object file
 */
#define CFE_PSP_MODULE_DECLARE_SIMPLE(name)              \
    void                name##_Init(uint32 PspModuleId); \
    CFE_PSP_ModuleApi_t CFE_PSP_##name##_API = {         \
        .ModuleType     = CFE_PSP_MODULE_TYPE_SIMPLE,    \
        .OperationFlags = 0,                             \
        .Init           = name##_Init,                   \
    }

/**
 * Initialize the included PSP modules.
 *
 * This is an optional part of the PSP and some PSPs may not use it.
 *
 * This function should only be called during PSP initialization before the
 * system is operational.  It is not intended to be called from application code after
 * CFE has started.  The function is not necessarily thread-safe and should be called
 * before any child threads are created.
 *
 * Note that this does _not_ return any status --
 * If a failure occurs during initialization that would make normal operation impossible,
 * then the module itself will call CFE_PSP_Panic() and this will not return.  Otherwise,
 * benign/recoverable failures are expected to be just that, and the calling code will not
 * need to take any special action either way.
 *
 * In short, if this function returns, then it means the system is good enough to continue.
 */
void CFE_PSP_ModuleInit(void);

/**
 * Search for a specific module name within a module list
 *
 * This is an internal helper function, but declared in a header for unit testing purposes.
 * This facilitates CFE_PSP_Module_FindByName and not intended to be called directly.
 *
 * \param WrapPtr    List to search
 * \param ModuleName Name to search for
 *
 * \returns Module ID of matching entry
 * \retval  0 if name does not appear in list
 */
uint32 CFE_PSP_Module_SearchNameInList(const CFE_PSP_ModuleListWrapper_t *WrapPtr, const char *ModuleName);

/**
 * Initialze a module list
 *
 * This is an internal helper function, but declared in a header for unit testing purposes.
 * This facilitates CFE_PSP_ModuleInit and not intended to be called directly.
 *
 * \param WrapPtr    Wrapper to initialize
 * \param BaseId     Module ID base to use for entries in list
 * \param ListPtr    Pointer to list.  Must be terminated with NULL name entry.
 */
void CFE_PSP_ModuleInitList(CFE_PSP_ModuleListWrapper_t *WrapPtr, uint32 BaseId, CFE_StaticModuleLoadEntry_t *ListPtr);

/**
 * Obtain the ID for a named module.
 *
 * Although this is currently prototyped as a function scoped to the PSP,
 * this prototype could be moved to the public area so the CFS could use this (TBD)
 *
 * \param ModuleName    Name of the module to look up
 * \param PspModuleId   Will be set to the ID of the module if successful
 * \returns CFE_PSP_SUCCESS if lookup succeeded
 */
int32 CFE_PSP_Module_FindByName(const char *ModuleName, uint32 *PspModuleId);

/**
 * Obtain the API for a specific module.
 *
 * \param PspModuleId   The ID of the module (configuration-dependent)
 * \param API           Will be set to the API structure if successful
 * \returns CFE_PSP_SUCCESS if lookup succeeded
 */
int32 CFE_PSP_Module_GetAPIEntry(uint32 PspModuleId, CFE_PSP_ModuleApi_t **API);

/**
 * \brief A list of fixed/base modules associated with the PSP
 *
 * This list should be generated by the build system based on the user-selected PSP
 */
extern CFE_StaticModuleLoadEntry_t CFE_PSP_BASE_MODULE_LIST[];

#endif /* CFE_PSP_MODULE_H_ */
