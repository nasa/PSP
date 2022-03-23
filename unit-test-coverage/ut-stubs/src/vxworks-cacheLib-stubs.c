/* PSP coverage stub replacement for cacheLib.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_cacheLib.h"

PCS_STATUS PCS_cacheTextUpdate(void *adrs, size_t bytes)
{
    return UT_DEFAULT_IMPL(PCS_cacheTextUpdate);
}
