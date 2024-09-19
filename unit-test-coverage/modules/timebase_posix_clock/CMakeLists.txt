######################################################################
#
# CMAKE build recipe for white-box coverage tests of VxWorks timebase module
#
add_definitions(-D_CFE_PSP_MODULE_)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/inc")
include_directories("${CFEPSP_SOURCE_DIR}/fsw/modules/iodriver/inc")
include_directories("${CFEPSP_SOURCE_DIR}/fsw/modules/timebase_posix_clock")

add_psp_covtest(timebase_posix_clock src/coveragetest-timebase_posix_clock.c
    ${CFEPSP_SOURCE_DIR}/fsw/modules/timebase_posix_clock/timebase_posix_clock.c
)
