#ifndef _PSP_STUB_CFE_CONFIGDATA_H_
#define _PSP_STUB_CFE_CONFIGDATA_H_

#include "PCS_basetypes.h"

#define PCS_CONFIG_MISSIONVERSION "UT-mission"
#define PCS_CONFIG_CFEVERSION     "UT-CFE"
#define PCS_CONFIG_OSALVERSION    "UT-OSAL"
#define PCS_CONFIG_CONFIGSTR      "UT-config"
#define PCS_CONFIG_DATESTR        "UT-date"
#define PCS_CONFIG_USERSTR        "UT-user"
#define PCS_CONFIG_CPUNAME        "UT-cpuname"
#define PCS_CONFIG_CPUNUMBER      111
#define PCS_CONFIG_SPACECRAFT     222

/**
 * Stub for the main system entry function implemented in CFE ES
 */
void PCS_SystemMain(uint32 StartType, uint32 StartSubtype, uint32 ModeId, const char *StartFilePath);

/**
 * Stub for 1Hz ISR function implemented in CFE TIME
 */
void PCS_System1HzISR(void);

/**
 * Stub for notification function implemented in CFE ES
 */
void PCS_SystemNotify(void);

#endif /* _PSP_STUB_CFE_CONFIGDATA_H_ */
