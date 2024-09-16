######################################################################
#
# CMAKE build recipe for white-box coverage tests of VxWorks timebase module
#
add_definitions(-D_CFE_PSP_MODULE_)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/inc")
#include_directories("${CFEPSP_SOURCE_DIR}/fsw/modules/iodriver/inc")
#include_directories("${CFEPSP_SOURCE_DIR}/fsw/modules/eeprom_mmap_file")

add_psp_covtest(eeprom_mmap_file coveragetest-eeprom_mmap_file.c
    ${CFEPSP_SOURCE_DIR}/fsw/modules/eeprom_mmap_file/cfe_psp_eeprom_mmap_file.c
)
