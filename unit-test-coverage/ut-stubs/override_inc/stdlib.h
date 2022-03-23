/* PSP coverage stub replacement for stdlib.h */
#ifndef OVERRIDE_STDLIB_H
#define OVERRIDE_STDLIB_H

#include "PCS_stdlib.h"

/* ----------------------------------------- */
/* mappings for declarations in stdlib.h */
/* ----------------------------------------- */

#define EXIT_SUCCESS PCS_EXIT_SUCCESS
#define EXIT_FAILURE PCS_EXIT_FAILURE
#define exit         PCS_exit
#define strtoul      PCS_strtoul
#define system       PCS_system
#define malloc       PCS_malloc
#define free         PCS_free

#endif
