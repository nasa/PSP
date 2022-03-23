/* PSP coverage stub replacement for string.h */
#ifndef OVERRIDE_STRING_H
#define OVERRIDE_STRING_H

#include "PCS_string.h"

/* ----------------------------------------- */
/* mappings for declarations in string.h */
/* ----------------------------------------- */
#define memcpy   PCS_memcpy
#define memset   PCS_memset
#define strcmp   PCS_strcmp
#define strcpy   PCS_strcpy
#define strlen   PCS_strlen
#define strncmp  PCS_strncmp
#define strncpy  PCS_strncpy
#define strchr   PCS_strchr
#define strrchr  PCS_strrchr
#define strcat   PCS_strcat
#define strncat  PCS_strncat
#define strerror PCS_strerror

#endif
