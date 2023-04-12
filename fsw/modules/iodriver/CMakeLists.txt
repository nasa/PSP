
# Generic I/O device driver interface module
add_psp_module(iodriver src/iodriver.c)

target_include_directories(iodriver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

if (ENABLE_UNIT_TESTS)
    add_subdirectory(ut-stubs)
endif (ENABLE_UNIT_TESTS)
