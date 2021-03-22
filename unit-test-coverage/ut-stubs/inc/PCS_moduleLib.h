/* PSP coverage stub replacement for moduleLib.h */
#ifndef _PSP_STUB_MODULELIB_H_
#define _PSP_STUB_MODULELIB_H_

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"

/* ----------------------------------------- */
/* constants normally defined in moduleLib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in moduleLib.h */
/* ----------------------------------------- */
typedef struct PCS_MODULE
{
    int m;
} PCS_MODULE;
typedef PCS_MODULE *PCS_MODULE_ID;

typedef struct PCS_MODULE_INFO
{
    struct
    {
        unsigned long textAddr;
        unsigned long textSize;
        unsigned long dataAddr;
        unsigned long dataSize;
        unsigned long bssAddr;
        unsigned long bssSize;
    } segInfo;

} PCS_MODULE_INFO;

/* ----------------------------------------- */
/* prototypes normally declared in moduleLib.h */
/* ----------------------------------------- */

extern PCS_STATUS    PCS_moduleInfoGet(PCS_MODULE_ID moduleId, PCS_MODULE_INFO *pModuleInfo);
extern PCS_MODULE_ID PCS_moduleFindByName(const char *moduleName);

#endif /* _PSP_STUB_MODULELIB_H_ */
