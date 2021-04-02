/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for string.h */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utstubs.h"

#include "common_types.h"
#include "target_config.h"

#include "PCS_cfe_configdata.h"

CFE_StaticModuleLoadEntry_t CFE_PSP_BASE_MODULE_LIST[] = {{NULL}};

Target_CfeConfigData GLOBAL_CFE_CONFIGDATA = {

    /**
     * 1Hz ISR entry point.  Called from PSP once per second on HW clock.
     */
    .System1HzISR = PCS_System1HzISR,

    /**
     * Main CFE entry point.  Called from PSP startup code.
     */
    .SystemMain = PCS_SystemMain,

    /**
     * Notification function. Called from PSP after async event handling.
     */
    .SystemNotify = PCS_SystemNotify};

Target_ConfigData GLOBAL_CONFIGDATA = {.MissionVersion       = PCS_CONFIG_MISSIONVERSION,
                                       .CfeVersion           = PCS_CONFIG_CFEVERSION,
                                       .OsalVersion          = PCS_CONFIG_OSALVERSION,
                                       .Config               = PCS_CONFIG_CONFIGSTR,
                                       .Date                 = PCS_CONFIG_DATESTR,
                                       .User                 = PCS_CONFIG_USERSTR,
                                       .Default_CpuName      = PCS_CONFIG_CPUNAME,
                                       .Default_CpuId        = PCS_CONFIG_CPUNUMBER,
                                       .Default_SpacecraftId = PCS_CONFIG_SPACECRAFT,
                                       .CfeConfig            = &GLOBAL_CFE_CONFIGDATA};

/**
 * Stub for the main system entry function implemented in CFE ES
 */
void PCS_SystemMain(uint32 StartType, uint32 StartSubtype, uint32 ModeId, const char *StartFilePath)
{
    UT_Stub_RegisterContextGenericArg(UT_KEY(PCS_SystemMain), StartType);
    UT_Stub_RegisterContextGenericArg(UT_KEY(PCS_SystemMain), StartSubtype);
    UT_Stub_RegisterContextGenericArg(UT_KEY(PCS_SystemMain), ModeId);
    UT_Stub_RegisterContextGenericArg(UT_KEY(PCS_SystemMain), StartFilePath);
    UT_DEFAULT_IMPL(PCS_SystemMain);
}

/**
 * Stub for 1Hz ISR function implemented in CFE TIME
 */
void PCS_System1HzISR(void)
{
    UT_DEFAULT_IMPL(PCS_System1HzISR);
}

/**
 * Stub for notification function implemented in CFE ES
 */
void PCS_SystemNotify(void)
{
    UT_DEFAULT_IMPL(PCS_SystemNotify);
}
