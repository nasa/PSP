/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
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

#ifndef CFE_PSP__CPUSET_H
#define CFE_PSP__CPUSET_H

#include <sys/syspage.h>
#include <sys/neutrino.h>

#include "osconfig.h"
#include "common_types.h"

/**
 * @brief PSP cpuset affinity structure
 *
 * This is used to represent the cpuset/affinity required by the QNX
 * operating system (struct _thread_runmask) to set the runmask and inherit mask.
 *
 * Applications should not directly access fields within this structure,
 * as the pointer configuration may change based on the number of processors in 
 * the running system.
 */
typedef struct
{
    int32    size;          /**< The size of the QNX run/inherit mask */
    uint32   *runmask;      /**< The QNX run mask pointer */
    uint32   *inherit_mask; /**< The QNX inherit mask pointer */
    uint32   mask_data[8];  /**< The QNX run mask and inherit mask storage (supports maximum of 128 processors) */
} CFE_PSP_cpuset_t;

/*-------------------------------------------------------------------------------------*/
/**
 * @brief Initialize and zero the cpuset/affinity structure
 *
 * @param[in]  cpuset The cpuset/affinity structure
 *
 */
static inline void CFE_PSP_CpusetZero(CFE_PSP_cpuset_t *cpuset)
{
    int32 mask_size = RMSK_SIZE(_syspage_ptr->num_cpu);

    /* Initialize/zero cpuset structure */
    memset(cpuset, 0x0, sizeof(CFE_PSP_cpuset_t));

    /* Set size of run mask and inherit mask */
    cpuset->size  = mask_size;

    /* Set run mask and inherit mask pointers */
    cpuset->runmask       = &cpuset->mask_data[0];
    cpuset->inherit_mask  = &cpuset->mask_data[mask_size];

    /*  Verify that cpuset has enought storage for cpus in system */
    if (((sizeof(uint32) * 3) + (sizeof(uint32) * mask_size * 2)) > sizeof(CFE_PSP_cpuset_t))
    {
        OS_printf(" Not enough storage for cpuset run and inherit mask: %s:%i \n", __func__, __LINE__);
    }
}

/*-------------------------------------------------------------------------------------*/
/**
 * @brief Set the corresponding cpu bit in the cpuset/affinity structure
 *
 * @param[in]  cpuset The cpuset/affinity structure
 * @param[in]  cpu    The cpu number to configure in cpuset/affinity structure
 *
 */
static inline void CFE_PSP_CpusetSetCore(CFE_PSP_cpuset_t *cpuset, int cpu)
{
    RMSK_SET(cpu, cpuset->runmask);
    RMSK_SET(cpu, cpuset->inherit_mask);
}

/*-------------------------------------------------------------------------------------*/
/**
 * @brief Clear the corresponding cpu bit in the cpuset/affinity structure
 *
 * @param[in]  cpuset The cpuset/affinity structure
 * @param[in]  cpu    The cpu number to configure in cpuset/affinity structure
 *
 */
static inline void CFE_PSP_CpusetClearCore(CFE_PSP_cpuset_t *cpuset, int cpu)
{
    RMSK_CLR(cpu, cpuset->runmask);
    RMSK_CLR(cpu, cpuset->inherit_mask);
}

/*-------------------------------------------------------------------------------------*/
/**
 * @brief Indicates if the corresponding cpu bit in the cpuset/affinity structure is set
 *
 * @param[in]  cpuset The cpuset/affinity structure
 * @param[in]  cpu    The cpu number to configure in cpuset/affinity structure
 *
 * @return     uint32 Indicates if cpu number is set in cpuset/affinity structure
 */
static inline uint32 CFE_PSP_CpusetIsSetCore(CFE_PSP_cpuset_t *cpuset, int cpu)
{
    return (RMSK_ISSET(cpu, cpuset->runmask) & RMSK_ISSET(cpu, cpuset->inherit_mask));
}

/*-------------------------------------------------------------------------------------*/
/**
 * @brief Set the corresponding cpu bit in the runmask of the cpuset/affinity structure
 *
 * @param[in]  cpuset The cpuset/affinity structure
 * @param[in]  cpu    The cpu number to configure in cpuset/affinity structure
 *
 */
static inline void CFE_PSP_CpusetSetCoreRunMask(CFE_PSP_cpuset_t *cpuset, int cpu)
{
    RMSK_SET(cpu, cpuset->runmask);
}

/*-------------------------------------------------------------------------------------*/
/**
 * @brief Clear the corresponding cpu bit in the runmask of the cpuset/affinity structure
 *
 * @param[in]  cpuset The cpuset/affinity structure
 * @param[in]  cpu    The cpu number to configure in cpuset/affinity structure
 *
 */
static inline void CFE_PSP_CpusetClearCoreRunMask(CFE_PSP_cpuset_t *cpuset, int cpu)
{
    RMSK_CLR(cpu, cpuset->runmask);
}

/*-------------------------------------------------------------------------------------*/
/**
 * @brief Indicates if the corresponding cpu bit in the runmask of the cpuset/affinity structure is set
 *
 * @param[in]  cpuset The cpuset/affinity structure
 * @param[in]  cpu    The cpu number to configure in cpuset/affinity structure
 *
 * @return     uint32 Indicates if cpu number is set in cpuset/affinity structure
 */
static inline uint32 CFE_PSP_CpusetIsSetCoreRunMask(CFE_PSP_cpuset_t *cpuset, int cpu)
{
    return (RMSK_ISSET(cpu, cpuset->runmask));
}

/*-------------------------------------------------------------------------------------*/
/**
 * @brief Set the corresponding cpu bit in the inherit mask of the cpuset/affinity structure
 *
 * @param[in]  cpuset The cpuset/affinity structure
 * @param[in]  cpu    The cpu number to configure in cpuset/affinity structure
 *
 */
static inline void CFE_PSP_CpusetSetCoreInheritMask(CFE_PSP_cpuset_t *cpuset, int cpu)
{
    RMSK_SET(cpu, cpuset->inherit_mask);
}

/*-------------------------------------------------------------------------------------*/
/**
 * @brief Clear the corresponding cpu bit in the inherit mask of the cpuset/affinity structure
 *
 * @param[in]  cpuset The cpuset/affinity structure
 * @param[in]  cpu    The cpu number to configure in cpuset/affinity structure
 *
 */
static inline void CFE_PSP_CpusetClearCoreInheritMask(CFE_PSP_cpuset_t *cpuset, int cpu)
{
    RMSK_CLR(cpu, cpuset->inherit_mask);
}

/*-------------------------------------------------------------------------------------*/
/**
 * @brief Indicates if the corresponding cpu bit in the inherit mask of the cpuset/affinity structure is set
 *
 * @param[in]  cpuset The cpuset/affinity structure
 * @param[in]  cpu    The cpu number to configure in cpuset/affinity structure
 *
 * @return     uint32 Indicates if cpu number is set in cpuset/affinity structure
 */
static inline uint32 CFE_PSP_CpusetIsSetCoreInheritMask(CFE_PSP_cpuset_t *cpuset, int cpu)
{
    return (RMSK_ISSET(cpu, cpuset->inherit_mask));
}

#endif /* CFE_PSP_CPUSET_H */
