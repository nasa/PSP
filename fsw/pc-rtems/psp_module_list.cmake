# This is a list of modules that is included as a fixed/base set
# when this PSP is selected.  They must exist under fsw/modules.

# NOTE: This set is REQUIRED for all versions of the platform.
# If a module only works on some versions of the platform, add
# if to psp_conditional_modules.cmake instead

soft_timebase
timebase_posix_clock
eeprom_notimpl
ram_direct
port_notimpl
iodriver
