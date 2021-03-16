/* PSP coverage stub replacement for fppLib.h */
#ifndef _PSP_STUB_FPPLIB_H_
#define _PSP_STUB_FPPLIB_H_

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

#endif /* _PSP_STUB_FPPLIB_H_ */
