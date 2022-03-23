/* PSP coverage stub replacement for sys/types.h */
#ifndef OVERRIDE_SYS_TYPES_H
#define OVERRIDE_SYS_TYPES_H

#include "PCS_sys_types.h"

/* ----------------------------------------- */
/* mappings for declarations in sys/types.h */
/* ----------------------------------------- */
#define ssize_t PCS_ssize_t
#define off_t   PCS_off_t
#define mode_t  PCS_mode_t
#define pid_t   PCS_pid_t
#define gid_t   PCS_gid_t
#define uid_t   PCS_uid_t

#endif
