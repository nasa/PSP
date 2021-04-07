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
    src/cfe_psp_exceptionstorage.c
    src/cfe_psp_memrange.c
    src/cfe_psp_memutils.c
    src/cfe_psp_module.c
    src/cfe_psp_version.c
)

target_compile_definitions(psp-${CFE_SYSTEM_PSPNAME}-shared PRIVATE
    $<TARGET_PROPERTY:psp_module_api,INTERFACE_COMPILE_DEFINITIONS>
)

target_include_directories(psp-${CFE_PSP_TARGETNAME}-shared PRIVATE
    $<TARGET_PROPERTY:psp_module_api,INTERFACE_INCLUDE_DIRECTORIES>
)
