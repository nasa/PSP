##########################################################################
#
# Default configuration options for PSP
#
# This file specifies the default values for various compile-time options
# supported by PSP.
#
# NOTE:
# The defaults in this file should _not_ be directly modified for tuning.
#
# Instead, use the "PSP_CONFIGURATION_FILE" CMake variable to define
# a custom file which can override/modify the configuration for the items
# which require tuning.
#
##########################################################################

##############################################################
# Code/Feature Selection Options for the PSP implementation
##############################################################


#
# PSP_CONFIG_DEBUG_PRINTF
# ----------------------------------
#
# Controls inclusion of PSP_DEBUG statements in the code
#
# If set FALSE, all PSP_DEBUG statements are compiled out.
#
# If set TRUE, all the "PSP_DEBUG" statements will be compiled in and displayed
# on the debug console.  The statements may still be suppressed at runtime.
#
set(PSP_CONFIG_DEBUG_PRINTF                    FALSE
    CACHE BOOL "Controls inclusion of PSP_DEBUG statements in the code"
)

#############################################
# Resource Limits for the PSP
#############################################

# The default value of debug level for PSP_DEBUG statements
set(PSP_CONFIG_DEBUG_LEVEL               1
    CACHE STRING "Default value of Debug level for PSP_DEBUG"
)

##############################################################
# FS Mapping for the PSP implementation
##############################################################


# The default virtual FS mapping for the "/cf" directory, typically used for Linux and QNX
set(PSP_CONFIG_CF_VIRTUAL_MAPPING              "./cf"
    CACHE STRING "Default virtual FS mapping for the /cf directory"
)

# The default virtual FS mapping for the EEPROM "/cf" directory, typically used for RTEMS
set(PSP_CONFIG_CF_EEPROM_VIRTUAL_MAPPING       "/mnt/eeprom"
    CACHE STRING "Default virtual FS mapping for the EEPROM /cf directory"
)

# The default virtual FS mapping for the ROMFS "/cf" directory, typically used for VxWorks 7.x
set(PSP_CONFIG_CF_ROMFS_VIRTUAL_MAPPING        "/romfs/cpu1/cf"
    CACHE STRING "Default virtual FS mapping for the ROMFS /cf directory"
)

# The default virtual FS mapping for the physical device "/cf" directory, typically used for VxWorks 6.9 (MCP750)
set(PSP_CONFIG_CF_PHY_DEV_VIRTUAL_MAPPING      "CF:0"
    CACHE STRING "Default virtual FS mapping for the physical device /cf directory"
)


