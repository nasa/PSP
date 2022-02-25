/* PSP coverage stub replacement for dosFsLib.h */
#ifndef PCS_DOSFSLIB_H
#define PCS_DOSFSLIB_H

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"

/* ----------------------------------------- */
/* constants normally defined in dosFsLib.h */
/* ----------------------------------------- */
#define PCS_DOS_CHK_ONLY        0x00000001
#define PCS_DOS_CHK_REPAIR      0x00000002
#define PCS_DOS_CHK_VERB_0      0x0000ff00 /* verbosity level/flags */
#define PCS_DOS_CHK_VERB_SILENT PCS_DOS_CHK_VERB_0
#define PCS_DOS_OPT_BLANK       0x0002 /* create a clean boot block */

/* ----------------------------------------- */
/* types normally defined in dosFsLib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in dosFsLib.h */
/* ----------------------------------------- */
extern PCS_STATUS PCS_dosFsVolFormat(char *path, int opt, PCS_FUNCPTR pPromptFunc);

#endif
