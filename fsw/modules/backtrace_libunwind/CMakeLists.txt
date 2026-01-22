
# Backtrace interface module for libunwind
add_psp_module(backtrace_libunwind src/cfe_psp_backtrace.c)

target_include_directories(backtrace_libunwind PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

if (ENABLE_UNIT_TESTS)
    add_subdirectory(ut-stubs)
endif (ENABLE_UNIT_TESTS)
