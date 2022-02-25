/* PSP coverage stub replacement for stdarg.h */
#ifndef PCS_STDARG_H
#define PCS_STDARG_H

#include "PCS_basetypes.h"

/* ----------------------------------------- */
/* constants normally defined in stdarg.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in stdarg.h */
/* ----------------------------------------- */
typedef struct
{
    void *p;
} PCS_va_list;

/* ----------------------------------------- */
/* prototypes normally declared in stdarg.h */
/* ----------------------------------------- */

#define PCS_va_start(ap, last) ap.p = &last
#define PCS_va_end(ap)

#endif
