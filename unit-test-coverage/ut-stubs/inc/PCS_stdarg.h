/* PSP coverage stub replacement for stdarg.h */
#ifndef _PSP_STUB_STDARG_H_
#define _PSP_STUB_STDARG_H_

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

#endif /* _PSP_STUB_STDARG_H_ */
