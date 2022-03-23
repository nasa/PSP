/* PSP coverage stub replacement for rebootLib.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_rebootLib.h"

void PCS_reboot(int boottype)
{
    UT_DEFAULT_IMPL(PCS_reboot);
}
