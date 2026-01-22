# This is a list of modules that is included as a fixed/base set
# when this PSP is selected.  They must exist under fsw/modules
#
# HLS - the vxworks_timebase only works on PowerPC platforms
#       we will use the posix_clock timebase here until a
#       hardware specific solution is foun
soft_timebase
timebase_posix_clock
eeprom_direct
ram_direct
port_direct
iodriver
# vxworks_sysmon
endian_api
