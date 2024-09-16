/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/**
 * @file
 *
 * Auto-Generated stub implementations for functions defined in PCS_unistd header
 */

#include "PCS_unistd.h"
#include "utgenstub.h"

void UT_DefaultHandler_PCS_gethostname(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_read(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_write(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_close()
 * ----------------------------------------------------
 */
int PCS_close(int fd)
{
    UT_GenStub_SetupReturnBuffer(PCS_close, int);

    UT_GenStub_AddParam(PCS_close, int, fd);

    UT_GenStub_Execute(PCS_close, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_close, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_getegid()
 * ----------------------------------------------------
 */
PCS_gid_t PCS_getegid(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_getegid, PCS_gid_t);

    UT_GenStub_Execute(PCS_getegid, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_getegid, PCS_gid_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_geteuid()
 * ----------------------------------------------------
 */
PCS_uid_t PCS_geteuid(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_geteuid, PCS_uid_t);

    UT_GenStub_Execute(PCS_geteuid, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_geteuid, PCS_uid_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_gethostid()
 * ----------------------------------------------------
 */
long int PCS_gethostid(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_gethostid, long int);

    UT_GenStub_Execute(PCS_gethostid, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_gethostid, long int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_gethostname()
 * ----------------------------------------------------
 */
int PCS_gethostname(char *name, size_t len)
{
    UT_GenStub_SetupReturnBuffer(PCS_gethostname, int);

    UT_GenStub_AddParam(PCS_gethostname, char *, name);
    UT_GenStub_AddParam(PCS_gethostname, size_t, len);

    UT_GenStub_Execute(PCS_gethostname, Basic, UT_DefaultHandler_PCS_gethostname);

    return UT_GenStub_GetReturnValue(PCS_gethostname, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_getpid()
 * ----------------------------------------------------
 */
PCS_pid_t PCS_getpid(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_getpid, PCS_pid_t);

    UT_GenStub_Execute(PCS_getpid, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_getpid, PCS_pid_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_lseek()
 * ----------------------------------------------------
 */
PCS_off_t PCS_lseek(int fd, PCS_off_t offset, int whence)
{
    UT_GenStub_SetupReturnBuffer(PCS_lseek, PCS_off_t);

    UT_GenStub_AddParam(PCS_lseek, int, fd);
    UT_GenStub_AddParam(PCS_lseek, PCS_off_t, offset);
    UT_GenStub_AddParam(PCS_lseek, int, whence);

    UT_GenStub_Execute(PCS_lseek, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_lseek, PCS_off_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_read()
 * ----------------------------------------------------
 */
PCS_ssize_t PCS_read(int fd, void *buf, size_t nbytes)
{
    UT_GenStub_SetupReturnBuffer(PCS_read, PCS_ssize_t);

    UT_GenStub_AddParam(PCS_read, int, fd);
    UT_GenStub_AddParam(PCS_read, void *, buf);
    UT_GenStub_AddParam(PCS_read, size_t, nbytes);

    UT_GenStub_Execute(PCS_read, Basic, UT_DefaultHandler_PCS_read);

    return UT_GenStub_GetReturnValue(PCS_read, PCS_ssize_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_rmdir()
 * ----------------------------------------------------
 */
int PCS_rmdir(const char *path)
{
    UT_GenStub_SetupReturnBuffer(PCS_rmdir, int);

    UT_GenStub_AddParam(PCS_rmdir, const char *, path);

    UT_GenStub_Execute(PCS_rmdir, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_rmdir, int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_sysconf()
 * ----------------------------------------------------
 */
long int PCS_sysconf(int name)
{
    UT_GenStub_SetupReturnBuffer(PCS_sysconf, long int);

    UT_GenStub_AddParam(PCS_sysconf, int, name);

    UT_GenStub_Execute(PCS_sysconf, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_sysconf, long int);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_write()
 * ----------------------------------------------------
 */
PCS_ssize_t PCS_write(int fd, const void *buf, size_t nbytes)
{
    UT_GenStub_SetupReturnBuffer(PCS_write, PCS_ssize_t);

    UT_GenStub_AddParam(PCS_write, int, fd);
    UT_GenStub_AddParam(PCS_write, const void *, buf);
    UT_GenStub_AddParam(PCS_write, size_t, nbytes);

    UT_GenStub_Execute(PCS_write, Basic, UT_DefaultHandler_PCS_write);

    return UT_GenStub_GetReturnValue(PCS_write, PCS_ssize_t);
}
