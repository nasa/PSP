######################################################################
#
# CMAKE build recipe for white-box coverage tests of VxWorks timebase module
#
######################################################################

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/inc")

add_psp_covtest(timebase_vxworks src/coveragetest-timebase_vxworks.c
    ${CFEPSP_SOURCE_DIR}/fsw/modules/timebase_vxworks/cfe_psp_timebase_vxworks.c
)
