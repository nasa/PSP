/* PSP coverage stub replacement for stdio.h */
#ifndef OVERRIDE_STDIO_H
#define OVERRIDE_STDIO_H

#include "PCS_stdio.h"

/* ----------------------------------------- */
/* mappings for declarations in stdio.h */
/* ----------------------------------------- */

#define FILE        PCS_FILE
#define fclose      PCS_fclose
#define fgets       PCS_fgets
#define fopen       PCS_fopen
#define fputs       PCS_fputs
#define remove      PCS_remove
#define rename      PCS_rename
#define snprintf    PCS_snprintf
#define vsnprintf   PCS_vsnprintf
#define printf(...) PCS_printf(__VA_ARGS__)
#define putchar     PCS_putchar

#define stdin  PCS_stdin
#define stdout PCS_stdout
#define stderr PCS_stderr

#endif
