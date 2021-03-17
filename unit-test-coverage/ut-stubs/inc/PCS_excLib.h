/* PSP coverage stub replacement for excLib.h */
#ifndef _PSP_STUB_EXCLIB_H_
#define _PSP_STUB_EXCLIB_H_

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

#endif /* _PSP_STUB_EXCLIB_H_ */
