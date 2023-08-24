
# Pseudo-terminal interface module
# add_definitions(-DDEBUG_BUILD)
add_psp_module(vxworks_sysmon vxworks_sysmon.c)
target_include_directories(vxworks_sysmon PRIVATE $<TARGET_PROPERTY:iodriver,INTERFACE_INCLUDE_DIRECTORIES>)
