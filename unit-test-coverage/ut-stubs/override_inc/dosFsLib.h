/* PSP coverage stub replacement for dosFsLib.h */
#ifndef OVERRIDE_DOSFSLIB_H
#define OVERRIDE_DOSFSLIB_H

#include "PCS_dosFsLib.h"
#include <vxWorks.h>

/* ----------------------------------------- */
/* mappings for declarations in dosFsLib.h */
/* ----------------------------------------- */
#define DOS_CHK_ONLY        PCS_DOS_CHK_ONLY
#define DOS_CHK_REPAIR      PCS_DOS_CHK_REPAIR
#define DOS_CHK_VERB_0      PCS_DOS_CHK_VERB_0
#define DOS_CHK_VERB_SILENT PCS_DOS_CHK_VERB_SILENT
#define DOS_OPT_BLANK       PCS_DOS_OPT_BLANK

#define dosFsVolFormat PCS_dosFsVolFormat

#endif
