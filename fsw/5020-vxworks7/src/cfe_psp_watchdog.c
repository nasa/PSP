/************************************************************************************************
**
** File: cfe_psp_watchdog.c
**
**      Copyright (c) 2004-2011, United States Government as represented by
**      Administrator for The National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      This is governed by the NASA Open Source Agreement and may be used,
**      distributed and modified only pursuant to the terms of that agreement.
**
** Purpose:
**   This file contains glue routines between the cFE and the OS Board Support Package (BSP).
**   The functions here allow the cFE to interface functions that are board and OS specific
**   and usually dont fit well in the OS abstraction layer.
**
*************************************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common_types.h"
#include "osapi.h"
#include "cfe_psp.h"


/*
** Global Variables
*/
uint32 CFE_PSP_WatchdogValue = 20000;  /* Watchdog time in msecs */


/******************************************************************************
**  Function:  CFE_PSP_WatchdogInit()
**
**  Purpose:
**    To setup the timer resolution and/or other settings custom to this platform
**
**  Arguments:
**    None
**
**  Return:
**    None
******************************************************************************/
void CFE_PSP_WatchdogInit(void)
{
	CFE_PSP_WatchdogSet(CFE_PSP_WatchdogValue);  /* in msecs */
}


/******************************************************************************
**  Function:  CFE_PSP_WatchdogEnable()
**
**  Purpose:
**    Enable the watchdog timer
**
**    If the processor BSP is set to define "ENABLE_STARTUP_WATCHDOG" in config.h or
**    using the kernel config tool, this function will be called in sysHwInit2()
**    in sysLib.c. The watchdog timer is disabled by default in startup firmware.
**    The defalut value for the WATCH DOG timer is defined by "STARTUP_WATCHDOG_TIMEOUT".
**
**  Arguments:
**    None
**
**  Return:
**    None
******************************************************************************/
void CFE_PSP_WatchdogEnable(void)
{
	//sysEnableFpgaWdt(1);
}


/******************************************************************************
**  Function:  CFE_PSP_WatchdogDisable()
**
**  Purpose:
**    Disable the watchdog timer
**
**  Arguments:
**    None
**
**  Return:
**    None
******************************************************************************/
void CFE_PSP_WatchdogDisable(void)
{
	//sysDisableFpgaWdt();
}


/******************************************************************************
**  Function:  CFE_PSP_WatchdogService()
**
**  Purpose:
**    Feed the watchdog timer
**
**  Arguments:
**    None
**
**  Return:
**    None
******************************************************************************/
void CFE_PSP_WatchdogService(void)
{
	/*
     * This function toggles the watchdog timer and it must be called at least
     * once every watchdog timer period if the watchdog timer is enabled.
     * Otherwise, the board will perform a reset once the timer expires.
     */
	//sysPulseFpgaWdt();
}


/******************************************************************************
**  Function:  CFE_PSP_WatchdogGet
**
**  Purpose:
**    Get the current watchdog value
**
**  Arguments:
**    None
**
**  Return:
**    The current watchdog value in msecs
******************************************************************************/
uint32 CFE_PSP_WatchdogGet(void)
{
   return((uint32)CFE_PSP_WatchdogValue);
}


/******************************************************************************
**  Function:  CFE_PSP_WatchdogSet
**
**  Purpose:
**    Get the current watchdog value
**
**  Arguments:
**    input - watchDogValue - The new watchdog value in msecs
**
**  Return:
**    None
******************************************************************************/
void CFE_PSP_WatchdogSet(uint32 watchDogValue)
{
#if 0
    float rate = 0.0;

    CFE_PSP_WatchdogValue = watchDogValue/1000;  /* in msecs */

    /*Rate is in seconds*/
    rate = (((float)watchDogValue)*0.001);
    sysSetFpgaWdt(rate);
#endif
}


