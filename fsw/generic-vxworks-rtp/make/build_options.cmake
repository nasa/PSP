##########################################################################
#
# Build options for "generic-vxworks" PSP
# This file specifies any global-scope compiler options when using this PSP
#
##########################################################################

# This indicates where to install target binaries created during the build
# Note - this should be phased out in favor of the staging dir from OSAL BSP
set(INSTALL_SUBDIR "cf")

# Some upper-level code may be gated on _VXWORKS_OS_ being defined
# This is for compatibility with older build scripts which defined this symbol,
# but no CFE/OSAL framework code depends on this symbol.
add_definitions("-D_VXWORKS_OS_")


# Use the <tbd>-specific VxWorks BSP include directory
# This needs to be globally used, not just private to the PSP, because
# some VxWorks headers reference files contained here.
# include_directories(
#    ${WIND_BASE}/target/config/<tbd>
# )

# therefore all code compiled for this platform should always define these symbols.
# for a "generic-vxworks" PSP, so I'm trying to keep architecture specific defs out of this 
add_definitions("-D__vx_sdk__")

set(CFE_PSP_EXPECTED_OSAL_BSPTYPE "generic-vxworks-rtp")

