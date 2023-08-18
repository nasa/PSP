
# Pseudo-terminal interface module
# add_definitions(-DDEBUG_BUILD)
add_psp_module(rtems_sysmon rtems_sysmon.c)
target_include_directories(rtems_sysmon PRIVATE $<TARGET_PROPERTY:iodriver,INTERFACE_INCLUDE_DIRECTORIES>)
