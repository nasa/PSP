/* PSP coverage stub replacement for stdlib.h */
#ifndef _PSP_STUB_STDLIB_H_
#define _PSP_STUB_STDLIB_H_

#include "PCS_basetypes.h"

/* ----------------------------------------- */
/* constants normally defined in stdlib.h */
/* ----------------------------------------- */

#define PCS_EXIT_SUCCESS 0x0100
#define PCS_EXIT_FAILURE 0x0101

/* ----------------------------------------- */
/* types normally defined in stdlib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in stdlib.h */
/* ----------------------------------------- */

extern void              PCS_exit(int status);
extern unsigned long int PCS_strtoul(const char *nptr, char **endptr, int base);
extern int               PCS_system(const char *command);
extern void *            PCS_malloc(size_t sz);
extern void              PCS_free(void *ptr);

#endif /* _PSP_STUB_STDLIB_H_ */
