/* PSP coverage stub replacement for ataDrv.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_drv_hdisk_ataDrv.h"

PCS_device_t PCS_ataXbdDevCreate(int ctrl, int drive, unsigned int nBlks, unsigned int offset, const char *name)
{
    return UT_DEFAULT_IMPL(PCS_ataXbdDevCreate);
}
