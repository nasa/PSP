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

#
# PSP_CONFIG_RAM_DIRECT_MODE
# ----------------------------------
#
# Controls inclusion of PSP RAM_DIRECT module 
#
# If set FALSE, the PSP RAM_NOTIMPL module included.
#
# If set TRUE, the PSP RAM_DIRECT module included.
#
set(PSP_CONFIG_RAM_DIRECT_MODE                 FALSE
    CACHE BOOL "Controls inclusion of PSP RAM_DIRECT module"
)

#
# PSP_CONFIG_RAM_DEBUG_SCRATCHPAD
# ----------------------------------
#
# Controls inclusion of the RAM scratchpad in a PSP module 
#
# If set FALSE, the RAM scratchpad is not included in a PSP module.
#
# If set TRUE, the RAM scratchpad is included in a PSP module.
#
set(PSP_CONFIG_RAM_DEBUG_SCRATCHPAD           FALSE
    CACHE BOOL "Controls inclusion of PSP RAM scratchpad module"
)

#
# PSP_CONFIG_RAM_DIRECT_STRICT_MODE
# --------------------------------------------
#
# Restrict access to CFE_PSP_MemValidateRange() address ranges
# within PSP RAM_DIRECT module
#
# If set FALSE, any addresses can be read or written.
#
# If set TRUE, only the CFE_PSP_MemValidateRange() address ranges
# can be read or written.
#
set(PSP_CONFIG_RAM_DIRECT_STRICT_MODE          FALSE
    CACHE BOOL "Restricts PSP RAM_DIRECT module access to CFE_PSP_MemValidateRange() address ranges"
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

# The default path for simulated EEPROM.DAT file
set(PSP_CONFIG_SIMULATED_EEPROM_FILE_PATH      "./cf"
    CACHE STRING "Default path for simulated EEPROM.DAT file"
)


