/* PSP coverage stub replacement for fppLib.h */
#ifndef PCS_FPPLIB_H
#define PCS_FPPLIB_H

#include "PCS_basetypes.h"

/* ----------------------------------------- */
/* constants normally defined in fppLib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in fppLib.h */
/* ----------------------------------------- */

typedef struct
{
    unsigned long context[4];
} PCS_FP_CONTEXT;

/* ----------------------------------------- */
/* prototypes normally declared in fppLib.h */
/* ----------------------------------------- */
extern void PCS_fppSave(PCS_FP_CONTEXT *fpc);

#endif
