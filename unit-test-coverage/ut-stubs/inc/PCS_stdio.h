/* PSP coverage stub replacement for stdio.h */
#ifndef _PSP_STUB_STDIO_H_
#define _PSP_STUB_STDIO_H_

#include "PCS_basetypes.h"
#include "PCS_stdarg.h"

/* ----------------------------------------- */
/* constants normally defined in stdio.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in stdio.h */
/* ----------------------------------------- */
typedef struct PCS_FILE PCS_FILE;

/* ----------------------------------------- */
/* prototypes normally declared in stdio.h */
/* ----------------------------------------- */

extern int       PCS_fclose(PCS_FILE *stream);
extern char *    PCS_fgets(char *s, int n, PCS_FILE *stream);
extern PCS_FILE *PCS_fopen(const char *filename, const char *modes);
extern int       PCS_fputs(const char *s, PCS_FILE *stream);
extern int       PCS_remove(const char *filename);
extern int       PCS_rename(const char *old, const char *nw);
extern int       PCS_snprintf(char *s, size_t maxlen, const char *format, ...);
extern int       PCS_vsnprintf(char *s, size_t maxlen, const char *format, PCS_va_list arg);
extern int       PCS_printf(const char *format, ...);
extern int       PCS_putchar(int c);

extern PCS_FILE *PCS_stdin;
extern PCS_FILE *PCS_stdout;
extern PCS_FILE *PCS_stderr;

#endif /* _PSP_STUB_STDIO_H_ */
