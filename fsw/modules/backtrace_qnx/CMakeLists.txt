
# Backtrace interface module for QNX
add_psp_module(backtrace_qnx src/cfe_psp_backtrace.c)

target_include_directories(backtrace_qnx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

if (ENABLE_UNIT_TESTS)
    add_subdirectory(ut-stubs)
endif (ENABLE_UNIT_TESTS)
