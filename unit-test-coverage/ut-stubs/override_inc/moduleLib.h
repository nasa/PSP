/* PSP coverage stub replacement for moduleLib.h */
#ifndef OVERRIDE_MODULELIB_H
#define OVERRIDE_MODULELIB_H

#include "PCS_moduleLib.h"
#include <vxWorks.h>

/* ----------------------------------------- */
/* mappings for declarations in moduleLib.h */
/* ----------------------------------------- */

#define MODULE_ID   PCS_MODULE_ID
#define MODULE_INFO PCS_MODULE_INFO

#define moduleInfoGet    PCS_moduleInfoGet
#define moduleFindByName PCS_moduleFindByName

#endif
