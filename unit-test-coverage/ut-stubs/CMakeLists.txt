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
# They are prefixed with "PCS_" and target code must be recompiled to
# call the PCS_ version of the syscall instead of the regular syscall.
# This is because in some circumstances for these calls the stub actually
# needs to invoke the real version or else weird things happen.
# This library includes stubs from all supported operating systems.  This
# is generally OK as we do not use any actual OS system headers
#
# These files are generally organized to match whatever header file
# defines the function. For instance, POSIX defines the "mqueue.h"
# header file which in turn provides mq_open, mq_close, etc.  So
# the PCS_mq_open, PCS_mq_close declarations are in overrides/mqueue.h, and
# the respective implementation is in posix-mqueue-stubs.c.
#
# This keeps things relatively organized, and by keeping the source files
# relatively small and targeted like this the linker should only pull in
# the PCS functions that are actually used.
#
add_library(ut_psp_libc_stubs STATIC EXCLUDE_FROM_ALL
    src/PCS_arch_ppc_vxPpcLib_handlers.c
    src/PCS_arch_ppc_vxPpcLib_stubs.c
    src/PCS_arpa_inet_handlers.c
    src/PCS_arpa_inet_stubs.c
    src/PCS_bsdnet_handlers.c
    src/PCS_bsdnet_stubs.c
    src/PCS_cacheLib_stubs.c
    src/PCS_cfe_configdata_stubs.c
    src/PCS_dosFsLib_stubs.c
    src/PCS_drv_hdisk_ataDrv_stubs.c
    src/PCS_drv_pci_pciConfigLib_handlers.c
    src/PCS_drv_pci_pciConfigLib_stubs.c
    src/PCS_errno_globals.c
    src/PCS_errnoLib_stubs.c
    src/PCS_excLib_stubs.c
    src/PCS_fcntl_stubs.c
    src/PCS_fppLib_stubs.c
    src/PCS_intLib_stubs.c
    src/PCS_moduleLib_handlers.c
    src/PCS_moduleLib_stubs.c
    src/PCS_netinet_in_stubs.c
    src/PCS_ramDrv_stubs.c
    src/PCS_rebootLib_stubs.c
    src/PCS_speLib_stubs.c
    src/PCS_spyLibP_stubs.c
    src/PCS_spyLib_stubs.c
    src/PCS_stdio_handlers.c
    src/PCS_stdio_stubs.c
    src/PCS_stdlib_handlers.c
    src/PCS_stdlib_stubs.c
    src/PCS_string_handlers.c
    src/PCS_string_stubs.c
    src/PCS_sys950Lib_stubs.c
    src/PCS_sysApi_stubs.c
    src/PCS_sysLib_handlers.c
    src/PCS_sysLib_stubs.c
    src/PCS_sys_mman_stubs.c
    src/PCS_sys_select_stubs.c
    src/PCS_sys_socket_handlers.c
    src/PCS_sys_socket_stubs.c
    src/PCS_sys_stat_handlers.c
    src/PCS_sys_stat_stubs.c
    src/PCS_taskLib_handlers.c
    src/PCS_taskLib_stubs.c
    src/PCS_time_handlers.c
    src/PCS_time_stubs.c
    src/PCS_unistd_handlers.c
    src/PCS_unistd_stubs.c
    src/PCS_xbdBlkDev_stubs.c
    src/vxworks-mcpx750-stubs.c
    src/PCS_timestampimpl_stubs.c
    src/PCS_todimpl_stubs.c
    src/PCS_threadimpl_stubs.c
    src/PCS_tasks_stubs.c
    src/PCS_object_stubs.c
    src/PCS_cpuuse_stubs.c
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
    src/cfe_psp_exceptionstorage_api_stubs.c
    src/cfe_psp_memory_stubs.c
    src/cfe_psp_module_stubs.c
)

target_link_libraries(ut_psp_cfe_stubs PRIVATE
    psp_module_api
    ut_assert
)
