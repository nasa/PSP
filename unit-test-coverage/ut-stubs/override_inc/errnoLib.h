/* PSP coverage stub replacement for errnoLib.h */
#ifndef OVERRIDE_ERRNOLIB_H
#define OVERRIDE_ERRNOLIB_H

#include "PCS_errnoLib.h"
#include <vxWorks.h>

/* -----------------------------------------  */
/* mappings for declarations in errnoLib.h */
/* -----------------------------------------  */
#define errnoGet PCS_errnoGet

#endif
