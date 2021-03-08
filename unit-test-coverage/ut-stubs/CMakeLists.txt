# ----------------------------------------
#    Stub libraries for coverage testing
# ----------------------------------------

# This provides suitable "stub" implementations of every 
# function call used internally by the various OSAL modules
# for which there is not a stub already defined.
#
# (Note this is not the public OSAL API - that is stubbed separately)
#
# This includes:
# - Stub versions of C library calls defined per ANSI C89/C99
#     i.e. memset, strcmp, etc - these should be relevant for all
#     supported operating systems as they are standard C
# - Stub versions of internal "shared" OSAL implementation functions
#     i.e. everything declared in the internal API.  These are needed by 
#     any coverage test referencing on the shared/ng OSAL layer.
#

# The "ut_libc_stubs" target provides stub versions of C library calls.
# They are prefixed with "OCS_" and target code must be recompiled to
# call the OCS_ version of the syscall instead of the regular syscall.
# This is because in some circumstances for these calls the stub actually 
# needs to invoke the real version or else weird things happen.  
# This library includes stubs from all supported operating systems.  This
# is generally OK as we do not use any actual OS system headers
#
# These files are generally organized to match whatever header file  
# defines the function. For instance, POSIX defines the "mqueue.h"
# header file which in turn provides mq_open, mq_close, etc.  So
# the OCS_mq_open, OCS_mq_close declarations are in overrides/mqueue.h, and 
# the respective implementation is in posix-mqueue-stubs.c.
#
# This keeps things relatively organized, and by keeping the source files 
# relatively small and targeted like this the linker should only pull in
# the OCS functions that are actually used. 
#
add_library(ut_psp_libc_stubs STATIC EXCLUDE_FROM_ALL
    src/libc-stdio-stubs.c
    src/libc-stdlib-stubs.c
    src/libc-string-stubs.c
    src/vxworks-ataDrv-stubs.c
    src/vxworks-cacheLib-stubs.c
    src/vxworks-moduleLib-stubs.c
    src/vxworks-taskLib-stubs.c
    src/vxworks-excLib-stubs.c
    src/vxworks-fppLib-stubs.c
    src/vxworks-mcpx750-stubs.c
    src/vxworks-rebootLib-stubs.c
    src/vxworks-sysLib-stubs.c
    src/vxworks-vxLib-stubs.c
)
    
target_include_directories(ut_libc_stubs PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_link_libraries(ut_psp_libc_stubs PRIVATE 
    psp_module_api
    ut_assert 
)
    
add_library(ut_psp_cfe_stubs STATIC EXCLUDE_FROM_ALL
    src/cfe-configdata-stubs.c
)

target_link_libraries(ut_psp_cfe_stubs PRIVATE 
    psp_module_api
    ut_assert 
)