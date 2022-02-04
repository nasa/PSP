/* PSP coverage stub replacement for excLib.h */
#ifndef PCS_EXCLIB_H
#define PCS_EXCLIB_H

#include "PCS_basetypes.h"
#include "PCS_taskLib.h"

/* ----------------------------------------- */
/* constants normally defined in excLib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in excLib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in excLib.h */
/* ----------------------------------------- */

extern void PCS_excHookAdd(void (*Hook)(PCS_TASK_ID, int, void *));

#endif
