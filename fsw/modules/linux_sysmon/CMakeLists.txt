
# Pseudo-terminal interface module
add_psp_module(linux_sysmon linux_sysmon.c)
target_include_directories(linux_sysmon PRIVATE $<TARGET_PROPERTY:iodriver,INTERFACE_INCLUDE_DIRECTORIES>)
