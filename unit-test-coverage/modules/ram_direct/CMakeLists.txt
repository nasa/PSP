######################################################################
#
# CMAKE build recipe for white-box coverage tests of VxWorks timebase module
#
add_definitions(-D_CFE_PSP_MODULE_)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/inc")
#include_directories("${CFEPSP_SOURCE_DIR}/fsw/modules/iodriver/inc")
#include_directories("${CFEPSP_SOURCE_DIR}/fsw/modules/ram_direct")

add_psp_covtest(ram_direct coveragetest-ram_direct.c
    ${CFEPSP_SOURCE_DIR}/fsw/modules/ram_direct/cfe_psp_ram_direct.c
)
