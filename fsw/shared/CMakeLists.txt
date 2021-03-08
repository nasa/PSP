######################################################################
#
# CMAKE build recipe for shared PSP component
#
######################################################################

# This contains supplemental code to support running CFE
# on a variety of targets.
#
# Note this shared PSP code is currently built against headers provided by the
# target implementation.  This makes it implementation-specific even though
# the same source code is used with multiple targets.

# Build the shared implementation as a library
add_library(psp-${CFE_PSP_TARGETNAME}-shared OBJECT
    src/cfe_psp_configdata.c
    src/cfe_psp_eeprom.c
    src/cfe_psp_exceptionstorage.c
    src/cfe_psp_memrange.c
    src/cfe_psp_memutils.c
    src/cfe_psp_module.c
    src/cfe_psp_port.c
    src/cfe_psp_ram.c
)

target_include_directories(psp-${CFE_PSP_TARGETNAME}-shared PRIVATE 
    $<TARGET_PROPERTY:psp-${CFE_PSP_TARGETNAME}-impl,INCLUDE_DIRECTORIES>
)
target_link_libraries(psp-${CFE_PSP_TARGETNAME}-shared PRIVATE psp_module_api)
