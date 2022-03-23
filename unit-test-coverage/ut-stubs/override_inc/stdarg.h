/* PSP coverage stub replacement for stdarg.h */
#ifndef OVERRIDE_STDARG_H
#define OVERRIDE_STDARG_H

#include "PCS_stdarg.h"

/* ----------------------------------------- */
/* mappings for declarations in stdarg.h */
/* ----------------------------------------- */

#define va_list            PCS_va_list
#define va_start(ap, last) PCS_va_start(ap, last)
#define va_end(ap)         PCS_va_end(ap)

#endif
