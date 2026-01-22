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

set(CFE_PSP_EXPECTED_OSAL_BSPTYPE "generic-vxworks")
