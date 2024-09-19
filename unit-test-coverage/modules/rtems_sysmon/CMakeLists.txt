######################################################################
#
# CMAKE build recipe for white-box coverage tests of VxWorks timebase module
#
add_definitions(-D_CFE_PSP_MODULE_)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/inc")
include_directories("${CFEPSP_SOURCE_DIR}/fsw/modules/iodriver/inc")
include_directories("${CFEPSP_SOURCE_DIR}/fsw/modules/rtems_sysmon")

add_psp_covtest(rtems_sysmon src/coveragetest-rtems_sysmon.c
    ${CFEPSP_SOURCE_DIR}/fsw/modules/rtems_sysmon/rtems_sysmon.c
)
