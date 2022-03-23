/**
 * \file
 *
 * A PSP module to satisfy the "RAM" API on systems which
 * cannot access physical memory directly.
 *
 * All functions return CFE_PSP_ERR_NOT_IMPLEMENTED
 */

#include "cfe_psp.h"
#include "cfe_psp_module.h"

CFE_PSP_MODULE_DECLARE_SIMPLE(ram_notimpl);

void ram_notimpl_Init(uint32 PspModuleId)
{
    /* Inform the user that this module is in use */
    printf("CFE_PSP: Physical RAM access not implemented\n");
}

int32 CFE_PSP_MemRead8(cpuaddr MemoryAddress, uint8 *ByteValue)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_MemWrite8(cpuaddr MemoryAddress, uint8 ByteValue)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_MemRead16(cpuaddr MemoryAddress, uint16 *uint16Value)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_MemWrite16(cpuaddr MemoryAddress, uint16 uint16Value)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_MemRead32(cpuaddr MemoryAddress, uint32 *uint32Value)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_MemWrite32(cpuaddr MemoryAddress, uint32 uint32Value)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}
