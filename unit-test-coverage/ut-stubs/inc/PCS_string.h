/* PSP coverage stub replacement for string.h */
#ifndef _PSP_STUB_STRING_H_
#define _PSP_STUB_STRING_H_

#include "PCS_basetypes.h"

/* ----------------------------------------- */
/* constants normally defined in string.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* types normally defined in string.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in string.h */
/* ----------------------------------------- */

extern void * PCS_memcpy(void *dest, const void *src, size_t n);
extern void * PCS_memset(void *s, int c, size_t n);
extern int    PCS_strcmp(const char *s1, const char *s2);
extern char * PCS_strcpy(char *dest, const char *src);
extern size_t PCS_strlen(const char *s);
extern int    PCS_strncmp(const char *s1, const char *s2, size_t n);
extern char * PCS_strncpy(char *dest, const char *src, size_t n);
extern char * PCS_strchr(const char *s, int c);
extern char * PCS_strrchr(const char *s, int c);
extern char * PCS_strcat(char *dest, const char *src);
extern char * PCS_strncat(char *dest, const char *src, size_t n);
extern char * PCS_strerror(int errnum);

#endif /* _PSP_STUB_STRING_H_ */
