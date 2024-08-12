#
# CMake recipe for PSP unit test stub functions
#

add_library(ut_psp_api_stubs
    src/cfe_psp_cache_api_stubs.c
    src/cfe_psp_cds_api_handlers.c
    src/cfe_psp_cds_api_stubs.c
    src/cfe_psp_eepromaccess_api_stubs.c
    src/cfe_psp_error_stubs.c
    src/cfe_psp_exception_api_handlers.c
    src/cfe_psp_exception_api_stubs.c
    src/cfe_psp_exceptionstorage_api_stubs.c
    src/cfe_psp_globaldata_stubs.c
    src/cfe_psp_id_api_handlers.c
    src/cfe_psp_id_api_stubs.c
    src/cfe_psp_memaccess_api_handlers.c
    src/cfe_psp_memaccess_api_stubs.c
    src/cfe_psp_memory_stubs.c
    src/cfe_psp_memrange_api_handlers.c
    src/cfe_psp_memrange_api_stubs.c
    src/cfe_psp_module_stubs.c
    src/cfe_psp_port_api_stubs.c
    src/cfe_psp_ssr_api_stubs.c
    src/cfe_psp_stubs.c
    src/cfe_psp_timertick_api_handlers.c
    src/cfe_psp_timertick_api_stubs.c
    src/cfe_psp_version_api_handlers.c
    src/cfe_psp_version_api_stubs.c
    src/cfe_psp_watchdog_api_handlers.c
    src/cfe_psp_watchdog_api_stubs.c
)

target_link_libraries(ut_psp_api_stubs PRIVATE
    psp_module_api
    ut_assert
)

add_library(ut_psp-${CFE_PSP_TARGETNAME}_stubs ALIAS ut_psp_api_stubs)
