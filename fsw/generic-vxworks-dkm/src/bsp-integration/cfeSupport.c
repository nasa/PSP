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

/*
** cFE Support routines
**
** This module is a collection of support routines needed to run the cFE on vxWorks.
**
*/

#include <stdio.h>
#include <string.h>
#include "vxWorks.h"
#include "taskLib.h"
#include "sysLib.h"
#include "symLib.h"
#include "loadLib.h"
#include "ioLib.h"
#include "errnoLib.h"
#include "usrLib.h"
#include "cacheLib.h"

/*
** Defines
*/
#define CFE_CORE_PATH_LEN 64
#define CFE_CORE_PATH_DEF "/romfs/cpu1/core-cpu1.exe"

/*
** External reference to wrs_kernel_text_start and wrs_kernel_text_end
** The cFE core needs these symbols, but when the cfe-core.o is loaded as a
** dynamic module, these symbols are not in the symbol table.
*/

extern void *wrs_kernel_text_start;
extern void *wrs_kernel_text_end;

/*
** External reference to the vxWorks symbol table
*/
extern SYMTAB_ID sysSymTbl;

/*
** Purpose:  This function returns the start address of the kernel code.
**
*/
void *GetWrsKernelTextStart(void)
{
    return (void *)&wrs_kernel_text_start;
}

/*
** Purpose:  This function returns the end address of the kernel code.
**
*/
void *GetWrsKernelTextEnd(void)
{
    return (void *)&wrs_kernel_text_end;
}

void showKernelCodeAddrs(void)
{
    printf("&wrs_kernel_text_start = 0x%lX\n",(unsigned long)&wrs_kernel_text_start);
    printf("&wrs_kernel_text_end = 0x%lX\n",(unsigned long)&wrs_kernel_text_end);
}

/*
** Purpose:  This function unzips ( if needed ) , loads, and starts the cFE core.
**
*/
int startCfeCore(char *cfepath)
{
    int         fd;
    int         status;
    MODULE_ID   moduleID;
    SYMBOL_DESC SymDesc;
    char       *symValue;
    void      (*cFEFuncPtr)(void);
    char        cfeCorePath[CFE_CORE_PATH_LEN];
    TASK_ID     cfeTaskId;

    /*
     * Copy the cFE Core path that was passed in
     */
    if (cfepath != NULL)
    {
       snprintf(cfeCorePath, CFE_CORE_PATH_LEN, "%s", cfepath);
    }
    else
    {
       strncpy(cfeCorePath, CFE_CORE_PATH_DEF, CFE_CORE_PATH_LEN);
    }

    printf("cFE Core path to load is: %s\n",cfeCorePath);

    /*
    ** Open the cFE core module
    */
    fd = open(cfeCorePath, O_RDONLY, 0);
    if (fd < 0)
    {
        printf("Error: Cannot open cFE core file: %s!\n", cfeCorePath);
        return -1;
    }
    else
    {
        printf("Opened %s.\n", cfeCorePath);
    }

    /*
    ** Load the cFE core
    */
    moduleID = loadModule(fd, LOAD_ALL_SYMBOLS);
    if (moduleID == NULL)
    {
        printf("Error: Cannot load cFE core module.\n");
        close(fd);
        return -1;
    }
    else
    {
        printf("Loaded %s module OK.\n", cfeCorePath);
    }

    /*
    ** Close the file
    */
    close(fd);

    /*
    ** Lookup the cFE core entry point
    */
    memset(&SymDesc, 0, sizeof(SYMBOL_DESC));
    SymDesc.mask = SYM_FIND_BY_NAME;
    SymDesc.name = "OS_BSPMain";

    status = symFind(sysSymTbl, &SymDesc);
    if (status == ERROR)
    {
        printf("Error: Cannot locate OS_BSPMain symbol.\n");
        return -1;
    }
    symValue = SymDesc.value;

    /*
    ** Call the cFE startup routine
    */
    cFEFuncPtr = (void *)symValue;

    /* spawn the async output helper task */
    cfeTaskId = taskSpawn("CFS_IDLE", 200, 0, 16384,
                                      (FUNCPTR)cFEFuncPtr,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (cfeTaskId == TASK_ID_ERROR)
    {
        printf("taskSpawn() Error - vxWorks errno %d\n", errno);
        return(-1);
    }

    /*
    ** Return to the vxWorks shell
    */
    return 0;
}
