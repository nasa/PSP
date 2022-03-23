/* PSP coverage stub replacement for excLib.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_excLib.h"

void PCS_excHookAdd(void (*Hook)(PCS_TASK_ID, int, void *))
{
    UT_DEFAULT_IMPL(PCS_excHookAdd);
}
