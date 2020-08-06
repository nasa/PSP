/************************************************************************************************
**
** File: cfe_psp_timer.c
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
#include <vxWorks.h>
#include <sysLib.h>
#include <vxLib.h>
#include "osapi.h"
#include "cfe.h"
#include "cfe_psp.h"
#include "cfe_time.h"
#include "target_config.h"

/*
** External Function Prototypes
*/

/*
** Function Prototypes
*/

/*
** Macro Definitions
*/


/* CFE_PSP_TIMER_LOW32_ROLLOVER
**
**   The number that the least significant 32 bits of the 64-bit timestamp returned
**   by CFE_PSP_Get_Timebase() rolls over.
**
**   If the lower 32 bits rolls at 1 second, then
**     CFE_PSP_TIMER_LOW32_ROLLOVER will be 1000000.
**   If the lower 32 bits rolls at its maximum value (2^32), then
**     CFE_PSP_TIMER_LOW32_ROLLOVER will be 0.
*/
#define CFE_PSP_TIMER_LOW32_ROLLOVER  0


static uint32 tickPerSecond = 0;


/******************************************************************************
**  Function:  CFE_PSP_GetTime()
**
**  Purpose:
**    Gets the value of the time from the hardware using the processor TBR
**
**  Arguments:
**    Output - pLocalTime - pointer to local time variable
**
**  Return:
**    None
******************************************************************************/
void CFE_PSP_GetTime(OS_time_t *pLocalTime)
{
    uint32 tbu = 0;
    uint32 tbl = 0;
    unsigned long long tb = 0;
    static uint32 errorCount = 0;

    if (pLocalTime != NULL)
    {

    	vxTimeBaseGet((UINT32 *)&tbu, (UINT32 *)&tbl);

        /* Re-assemble the 64-bit count */
        tb = ((unsigned long long)tbu << 32) | (unsigned long long)tbl;
        /*if the ticks per second is zero initialize it.
         * The SP0 value is 41666666 and the SP0-S value is 49999999
         */
        if (tickPerSecond == 0)
        {
            tickPerSecond = sysTimestampFreq();
        }
        if (tickPerSecond != 0)
        {
                /* Convert to seconds and microseconds using only integer computations.
                 * The max seconds value is 442721864852  for the SP0 and 36893488221 for
                 * the SP0-S. The conversion below will cause a loss of data which is just
                 * a roll over of the clock for the local time defined in osal.
                 */
                pLocalTime->seconds   = (tb / tickPerSecond);
                pLocalTime->microsecs = ((tb % tickPerSecond) * 1000000 )/(tickPerSecond);

        }
        else if (errorCount < 2)
        {
            OS_printf("CFE_PSP: CFE_PSP_GetTime() - tickPerSecond equals zero.\n");
            errorCount++;
        }
    }

}

/******************************************************************************
**  Function:  CFE_PSP_Get_Timer_Tick()
**
**  Purpose:
**    Provides a common interface to system clock tick. This routine
**    is in the BSP because it is sometimes implemented in hardware and
**    sometimes taken care of by the RTOS.
**
**  Arguments:
**    None
**
**  Return:
**    OS system clock ticks per second
******************************************************************************/
uint32 CFE_PSP_Get_Timer_Tick(void)
{
   return ((uint32)sysClkRateGet());
}


/******************************************************************************
**  Function:  CFE_PSP_GetTimerTicksPerSecond()
**
**  Purpose:
**    Provides number of timer ticks per second
**
**  Arguments:
**    None
**
**  Return:
**    Value of ticks per second  returned by sysTimestampFreq
******************************************************************************/
uint32 CFE_PSP_GetTimerTicksPerSecond(void)
{
    return (tickPerSecond);
}


/******************************************************************************
**  Function:  CFE_PSP_GetTimerLow32Rollover()
**
**  Purpose:
**    Provides the value of the least significant 32 bits of the 64-bit timestamp
**
**  Arguments:
**    None
**
**  Return:
**    Value of CFE_PSP_TIMER_LOW32_ROLLOVER macro constant
******************************************************************************/
uint32 CFE_PSP_GetTimerLow32Rollover(void)
{
    return ((uint32)CFE_PSP_TIMER_LOW32_ROLLOVER);
}


/******************************************************************************
**  Function:  CFE_PSP_Get_Timebase()
**
**  Purpose:
**    Provides the Time-Base Register (TBR) values
**
**  Arguments:
**    Output - tbu - pointer to tbu variable
**    Output - tbl - pointer to tbl variable
**
**  Return:
**      Time-Base Register (TBR) values
******************************************************************************/
void CFE_PSP_Get_Timebase(uint32 *tbu, uint32* tbl)
{
    if ((tbu != NULL) && (tbl != NULL))
    {
        vxTimeBaseGet((UINT32 *)tbu, (UINT32 *)tbl);
    }
}


/******************************************************************************
**  Function:  CFE_PSP_Get_Dec()
**
**  Purpose:
**    Provides a common interface to decrementer counter. This routine
**    is in the BSP because it is sometimes implemented in hardware and
**    sometimes taken care of by the RTOS.
**
**  Arguments:
**    None
**
**  Return:
**    ??? value
******************************************************************************/
uint32 CFE_PSP_Get_Dec(void)
{
   return ((uint32)vxDecGet());
}


