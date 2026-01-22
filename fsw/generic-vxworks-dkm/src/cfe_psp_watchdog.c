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

/************************************************************************************************
** File:  cfe_psp_watchdog.c
**
** Purpose:
**   This file contains glue routines between the cFE and the OS Board Support Package ( BSP ).
**   The functions here allow the cFE to interface functions that are board and OS specific
**   and usually don't fit well in the OS abstraction layer.
**
** History:
**   2009/07/20  A. Cudmore    | Initial version,
**
*************************************************************************************************/

/*
**  Include Files
*/

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"

/*
**  System Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "vxWorks.h"
#include <hwif/drv/watchdog/vxbWatchdog.h>
#include "ioLib.h"
#include "iosLib.h"
#include "fioLib.h"

/*
** Types and prototypes for this module
*/
#include "cfe_psp.h"
#include "cfe_psp_config.h"

/*
** Global data
*/

/*
** The watchdog time in milliseconds
*/
uint32 CFE_PSP_WatchdogValue = CFE_PSP_WATCHDOG_MAX;

/*
 * File descriptor for watchdog (initialized to invalid val)
 */
int CFE_PSP_WatchdogFd = ERROR;

/**
 * Note: this implementation uses the vxbVirtualTimerWatchdog component
 * which works easily on all platforms but is not as reliable as a hardware
 * watchdog. As such, this watchdog cannot have the platform recover from
 * hard CPU lockups. When supporting a specific platform, be sure to use
 * its hardware watchdog capabilities. If there are no hardware watchdog
 * capabilities, then this virtual watchdog implementation is a good option.
 * 
 * Additionally, be sure to set VIRT_WDT_NO_REBOOT component to FALSE to 
 * enable reboot capabilities. This can be found in workbench by either 
 * searching for it in kernel config or by navigating to
 * VIP -> Harware -> Watchdog -> Virtual Timer Watchdog
 */

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CFE_PSP_WatchdogInit(void)
{
    DEV_HDR *WatchdogHeader;
    STATUS Status;
    struct watchdog_info WatchdogInfo;
    int WatchdogOptions;


    /* check to see if the virtual watchdog device has been installed. This is
     * done automatically when VIP is configured with DRV_VIRTUAL_TIMER_WATCHDOG */
    WatchdogHeader = iosDevFindExact("/watchdog/0");
    if (WatchdogHeader == NULL)
    {
        printf("failed to initialize watchdog driver. Be sure to add DRV_VIRTUAL_TIMER_WATCHDOG component to VxWorks VIP\n");
        return;
    }

    /* create a handle to access the watchdog as a IO device. Since we will be
     * writing and reading from the watchdog, we need to have read/write
     * capabilities, hence the UPDATE param (see ioLib.h for more details).
     * The watchdog should only be written to by the PSP so perms get set to
     * read/write for user and read only otherwise. */
    CFE_PSP_WatchdogFd = open("/watchdog/0", O_RDWR, 644);
    if (CFE_PSP_WatchdogFd < 0)
    {
        printf("failed to initialize watchdog file desc\n");
        return;
    }

    /* According to the WindRiver docs on the virtual watchdog timer, the 
     * watchdog is activated when the file is opened. The default timeout 
     * is 60 seconds. Thus, to avoid having the timer expire from just
     * calling CFE_PSP_WatchdogInit(), we disable the watchdog here */
    WatchdogOptions = WDIOS_DISABLECARD;
    Status = ioctl(CFE_PSP_WatchdogFd, WDIOC_SETOPTIONS, &WatchdogOptions);
    if (Status != OK) {
        printf("failed to initialize watchdog\n");
        close(CFE_PSP_WatchdogFd);
    }

    /* watchdog command to get info about the watchdog. Stored in WatchdogInfo.
     * (see watchdog.h located in VIP kernel header files for more detail). */
    Status = ioctl(CFE_PSP_WatchdogFd, WDIOC_GETSUPPORT, &WatchdogInfo);
    if (Status != OK)
    {
        printf("failed to get watchdog info\n");
        close(CFE_PSP_WatchdogFd);
    }
    else
    {
        printf("initialized watchdog with name: %s version: %u flags: %u\n", WatchdogInfo.name, WatchdogInfo.version, WatchdogInfo.flags);
    }
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CFE_PSP_WatchdogEnable(void)
{
    STATUS Status;
    int WatchdogOptions;

    if (CFE_PSP_WatchdogFd < 0) {
        printf("failed to initialize watchdog beforehand\n");
        return;
    }

    /* See vxbVirtualTimerWatchdog WindRiver docs for more detail */
    WatchdogOptions = WDIOS_ENABLECARD;
    Status = ioctl(CFE_PSP_WatchdogFd, WDIOC_SETOPTIONS, &WatchdogOptions);
    if (Status != OK) {
        printf("failed to enable watchdog\n");
        close(CFE_PSP_WatchdogFd);
    }
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CFE_PSP_WatchdogDisable(void)
{
    STATUS Status;
    int WatchdogOptions;

    if (CFE_PSP_WatchdogFd < 0) {
        printf("failed to initialize watchdog beforehand\n");
        return;
    }

    WatchdogOptions = WDIOS_DISABLECARD;
    Status = ioctl(CFE_PSP_WatchdogFd, WDIOC_SETOPTIONS, &WatchdogOptions);
    if (Status != OK) {
        printf("failed to disable watchdog\n");
        close(CFE_PSP_WatchdogFd);
    }
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CFE_PSP_WatchdogService(void)
{
    STATUS Status;
    
    if (CFE_PSP_WatchdogFd < 0) {
        printf("failed to initialize watchdog beforehand\n");
        return;
    }

    Status = ioctl(CFE_PSP_WatchdogFd, WDIOC_KEEPALIVE, 0);
    if (Status != OK) {
        printf("failed to service watchdog\n");
        close(CFE_PSP_WatchdogFd);
    }
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
uint32 CFE_PSP_WatchdogGet(void)
{
    STATUS Status;
    uint32 WatchdogValue;

    if (CFE_PSP_WatchdogFd < 0) {
        printf("failed to initialize watchdog beforehand\n");
        return 0;
    }

    WatchdogValue = 0;
    Status = ioctl(CFE_PSP_WatchdogFd, WDIOC_GETTIMEOUT, &WatchdogValue);
    if (Status != OK) {
        printf("failed to get watchdog timeout\n");
        close(CFE_PSP_WatchdogFd);
    }

    CFE_PSP_WatchdogValue = WatchdogValue;

    return CFE_PSP_WatchdogValue;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CFE_PSP_WatchdogSet(uint32 WatchdogValue)
{
    STATUS Status;

    if (CFE_PSP_WatchdogFd < 0) {
        printf("failed to initialize watchdog beforehand\n");
        return;
    }

    Status = ioctl(CFE_PSP_WatchdogFd, WDIOC_SETTIMEOUT, &WatchdogValue);
    if (Status != OK) {
        printf("failed to set watchdog timeout\n");
        close(CFE_PSP_WatchdogFd);
    }

    CFE_PSP_WatchdogValue = WatchdogValue;
}
