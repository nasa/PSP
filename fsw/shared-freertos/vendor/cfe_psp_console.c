/*
 * Copyright 2021 Patrick Paul
 * SPDX-License-Identifier: MIT-0
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "osapi.h"
#include "os-shared-common.h"

#include "cfe_psp.h"

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>


// char debugBuffer[100];
// #define DEBUG_BUFFER_SIZE (sizeof(debugBuffer)/sizeof(debugBuffer[0]))

int32 PSP_Console_Init(void)
{
    // No action. 
    // See also HLP_vSystemConfig() following .../osal/src/bsp/generic-freertos/src/bsp_start.c

    return CFE_PSP_SUCCESS;
}

