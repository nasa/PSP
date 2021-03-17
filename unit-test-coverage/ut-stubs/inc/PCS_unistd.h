/* PSP coverage stub replacement for unistd.h */
#ifndef _PSP_STUB_UNISTD_H_
#define _PSP_STUB_UNISTD_H_

#include "PCS_basetypes.h"
#include "PCS_sys_types.h"

/* ----------------------------------------- */
/* constants normally defined in unistd.h */
/* ----------------------------------------- */

#define PCS_SEEK_SET      0x1C01
#define PCS_SEEK_CUR      0x1C02
#define PCS_SEEK_END      0x1C03
#define PCS_STDIN_FILENO  0x1C04
#define PCS_STDOUT_FILENO 0x1C05
#define PCS_STDERR_FILENO 0x1C06

/* ----------------------------------------- */
/* types normally defined in unistd.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in unistd.h */
/* ----------------------------------------- */

extern int         PCS_close(int fd);
extern PCS_gid_t   PCS_getegid(void);
extern PCS_uid_t   PCS_geteuid(void);
extern long int    PCS_gethostid(void);
extern int         PCS_gethostname(char *name, size_t len);
extern PCS_pid_t   PCS_getpid(void);
extern PCS_off_t   PCS_lseek(int fd, PCS_off_t offset, int whence);
extern PCS_ssize_t PCS_read(int fd, void *buf, size_t nbytes);
extern int         PCS_rmdir(const char *path);
extern long int    PCS_sysconf(int name);
extern PCS_ssize_t PCS_write(int fd, const void *buf, size_t n);

#endif /* _PSP_STUB_UNISTD_H_ */
