######################################################################
#
# CMAKE build recipe for white-box coverage tests of rtems_sysmon
#
add_definitions(-D_CFE_PSP_MODULE_)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/inc")
include_directories("${CFEPSP_SOURCE_DIR}/fsw/modules/iodriver/inc")
include_directories("${CFEPSP_SOURCE_DIR}/fsw/modules/rtems_sysmon")

add_psp_covtest(rtems_sysmon src/coveragetest-rtems_sysmon.c
    src/coveragetest-rtems_sysmon_utils.c
    ${CFEPSP_SOURCE_DIR}/fsw/modules/rtems_sysmon/rtems_sysmon.c
)
