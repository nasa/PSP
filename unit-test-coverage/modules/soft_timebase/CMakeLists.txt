######################################################################
#
# CMAKE build recipe for white-box coverage tests of VxWorks timebase module
#
add_definitions(-D_CFE_PSP_MODULE_)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/inc")

add_psp_covtest(soft_timebase coveragetest-soft_timebase.c
    ${CFEPSP_SOURCE_DIR}/fsw/modules/soft_timebase/cfe_psp_soft_timebase.c
)
