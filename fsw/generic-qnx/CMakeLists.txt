######################################################################
#
# CMAKE build recipe for generic-qnx PSP component
#
######################################################################

# This contains the fully platform-specific code to
# run CFE on this target.

# Build the pc-linux implementation as a library
add_library(psp-${CFE_PSP_TARGETNAME}-impl OBJECT
    src/cfe_psp_exception.c
    src/cfe_psp_memory.c
    src/cfe_psp_ssr.c
    src/cfe_psp_start.c
    src/cfe_psp_support.c
    src/cfe_psp_watchdog.c
)

# The _GNU_SOURCE directive is required to call non-posix APIs
# that are specific to the Linux/glibc environment.
# Code outside the pc-linux PSP should _not_ depend on this.
target_compile_definitions(psp-${CFE_SYSTEM_PSPNAME}-impl PRIVATE
    _GNU_SOURCE
    $<TARGET_PROPERTY:psp_module_api,INTERFACE_COMPILE_DEFINITIONS>
)

target_include_directories(psp-${CFE_PSP_TARGETNAME}-impl PRIVATE
    inc
    $<TARGET_PROPERTY:psp_module_api,INTERFACE_INCLUDE_DIRECTORIES>
)

# Include definition of cfe_psp_backtrace.h referenced by cfe_psp_config.h
if (QNX_SDP_VERSION EQUAL 800)
    target_include_directories(psp-${CFE_PSP_TARGETNAME}-impl PRIVATE $<TARGET_PROPERTY:backtrace_libunwind,INTERFACE_INCLUDE_DIRECTORIES>)
elseif (QNX_SDP_VERSION EQUAL 710) 
    target_include_directories(psp-${CFE_PSP_TARGETNAME}-impl PRIVATE $<TARGET_PROPERTY:backtrace_qnx,INTERFACE_INCLUDE_DIRECTORIES>)
endif()

