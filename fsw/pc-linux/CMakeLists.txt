######################################################################
#
# CMAKE build recipe for pc-linux PSP component
#
######################################################################

# This contains the fully platform-specific code to 
# run CFE on this target.

include_directories(inc) 

# Build the pc-linux implementation as a library
add_library(psp-${CFE_PSP_TARGETNAME}-impl OBJECT
    src/cfe_psp_exception.c
    src/cfe_psp_memory.c
    src/cfe_psp_memtab.c
    src/cfe_psp_ssr.c
    src/cfe_psp_start.c
    src/cfe_psp_support.c
    src/cfe_psp_timer.c
    src/cfe_psp_watchdog.c)

# The _GNU_SOURCE directive is required to call non-posix APIs
# that are specific to the Linux/glibc environment.
# Code outside the pc-linux PSP should _not_ depend on this.
target_compile_definitions(psp-${CFE_SYSTEM_PSPNAME}-impl PRIVATE
    _GNU_SOURCE
)