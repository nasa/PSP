/************************************************************************************************
**
** File: cfe_psp_voltab.c
**
**      Copyright (c) 2004-2011, United States Government as represented by 
**      Administrator for The National Aeronautics and Space Administration. 
**      All Rights Reserved.
**
**      This is governed by the NASA Open Source Agreement and may be used,
**      distributed and modified only pursuant to the terms of that agreement. 
**
** Purpose: 
**   PSP Volume table for file systems
**
*************************************************************************************************/

/*
**  Include Files
*/
#include "common_types.h"
#include "osapi.h"


/*
** Macro Definitions
*/
#ifdef VOLTAB_PATH

#define VOLTAB_MACRO                                                                  \
    OS_VolumeInfo_t OS_VolumeTable [NUM_TABLE_ENTRIES] =                              \
    {                                                                                 \
        {"/ramdev0", " ",         RAM_DISK, TRUE,  TRUE,  FALSE, "",  "",   0    }, \
        {"/eedev0",      VOLTAB_PATH, FS_BASED, FALSE, FALSE, TRUE,  "CF", "/cf", 1024 }, \
        {"/ramdev1", " ",         RAM_DISK, TRUE,  TRUE,  FALSE, " ",  " ",   0    }, \
        {"/ramdev2", " ",         RAM_DISK, TRUE,  TRUE,  FALSE, " ",  " ",   0    }, \
        {"/ramdev3", " ",         RAM_DISK, TRUE,  TRUE,  FALSE, " ",  " ",   0    }, \
        {"/ramdev4", " ",         RAM_DISK, TRUE,  TRUE,  FALSE, " ",  " ",   0    }, \
        {"/ramdev5", " ",         RAM_DISK, TRUE,  TRUE,  FALSE, " ",  " ",   0    }, \
        {"unused",   "unused",    FS_BASED, TRUE,  TRUE,  FALSE, " ",  " ",   0    }, \
        {"unused",   "unused",    FS_BASED, TRUE,  TRUE,  FALSE, " ",  " ",   0    }, \
        {"unused",   "unused",    FS_BASED, TRUE,  TRUE,  FALSE, " ",  " ",   0    }, \
        {"unused",   "unused",    FS_BASED, TRUE,  TRUE,  FALSE, " ",  " ",   0    }, \
        {"unused",   "unused",    FS_BASED, TRUE,  TRUE,  FALSE, " ",  " ",   0    }, \
        {"unused",   "unused",    FS_BASED, TRUE,  TRUE,  FALSE, " ",  " ",   0    }, \
        {"unused",   "unused",    FS_BASED, TRUE,  TRUE,  FALSE, " ",  " ",   0    }  \
    };

VOLTAB_MACRO

#else  /* !VOLTAB_PATH */

/* 
** OSAL volume table
**
** This is the only file in the PSP that still has the OS_ naming convention,
** since it belongs to the OSAL. 
*/
OS_VolumeInfo_t OS_VolumeTable [NUM_TABLE_ENTRIES] = 
{
    /* DevName, PhysDev, VolType, Volatile?, Free?, IsMounted?, VolName, MountPoint, BlockSize */

    /* cFE RAM Disk */
    {"/ramdev0", " ", RAM_DISK, TRUE, TRUE, FALSE, " ", " ", 0 },

    /* Map Non-Volatile Disk to Mounted-Host Disk (tgtsvr) */
    /* since there is not currently a local flash disk */
    {"/eedev0", "host:/cf", FS_BASED, FALSE, FALSE, TRUE, "CF", "/cf", 1024 },

    /* Spare RAM Disks to be used for SSR and other RAM Disks */
    {"/ramdev1", "/ram0", FS_BASED, TRUE, FALSE, TRUE, "RD", "/rd", 1024 },
    {"/ramdev2", " ", RAM_DISK, TRUE, TRUE, FALSE, " ", " ", 0 },
    {"/ramdev3", " ", RAM_DISK, TRUE, TRUE, FALSE, " ", " ", 0 },
    {"/ramdev4", " ", RAM_DISK, TRUE, TRUE, FALSE, " ", " ", 0 },
    {"/ramdev5", " ", RAM_DISK, TRUE, TRUE, FALSE, " ", " ", 0 },

    {"unused", "unused", FS_BASED, TRUE, TRUE, FALSE, " ", " ", 0 },
    {"unused", "unused", FS_BASED, TRUE, TRUE, FALSE, " ", " ", 0 },
    {"unused", "unused", FS_BASED, TRUE, TRUE, FALSE, " ", " ", 0 },
    {"unused", "unused", FS_BASED, TRUE, TRUE, FALSE, " ", " ", 0 },
    {"unused", "unused", FS_BASED, TRUE, TRUE, FALSE, " ", " ", 0 },
    {"unused", "unused", FS_BASED, TRUE, TRUE, FALSE, " ", " ", 0 },
    {"unused", "unused", FS_BASED, TRUE, TRUE, FALSE, " ", " ", 0 }

    /* cFE Non-Volatile Disk -- Auto-Mapped to an existing CF disk */
    /*{"/eedev0", "CF:0", FS_BASED, FALSE, FALSE, TRUE, "CF", "/cf", 512 },*/

    /* Hard Disk mappings */
    /*{"/ssrdev0", "/hd:0/SSR1", FS_BASED, TRUE, TRUE, FALSE, " ", " ", 0 },*/
    /*{"/ssrdev1", "/hd:0/SSR2", FS_BASED, TRUE, TRUE, FALSE, " ", " ", 0 },*/
    /*{"/ssrdev2", "/hd:0/SSR3", FS_BASED, TRUE, TRUE, FALSE, " ", " ", 0 },*/
};

#endif /* VOLTAB_PATH */


