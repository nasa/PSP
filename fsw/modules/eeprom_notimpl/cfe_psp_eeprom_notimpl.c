/**
 * \file
 *
 * A PSP module to satisfy the "EEPROM" API on systems which
 * do not have an EEPROM or otherwise cannot access it.
 *
 * All functions return CFE_PSP_ERR_NOT_IMPLEMENTED
 */

#include "cfe_psp.h"
#include "cfe_psp_module.h"

CFE_PSP_MODULE_DECLARE_SIMPLE(eeprom_notimpl);

void eeprom_notimpl_Init(uint32 PspModuleId)
{
    /* Inform the user that this module is in use */
    printf("CFE_PSP: EEPROM access not implemented\n");
}

int32 CFE_PSP_EepromWrite32(cpuaddr MemoryAddress, uint32 uint32Value)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_EepromWrite16(cpuaddr MemoryAddress, uint16 uint16Value)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_EepromWrite8(cpuaddr MemoryAddress, uint8 ByteValue)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_EepromWriteEnable(uint32 Bank)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_EepromWriteDisable(uint32 Bank)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_EepromPowerUp(uint32 Bank)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_EepromPowerDown(uint32 Bank)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}
