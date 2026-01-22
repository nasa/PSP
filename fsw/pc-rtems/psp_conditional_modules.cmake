# The sysmon module only works in RTEMS >= 5.
# Ideally this check should be VERSION_GREATER_EQUAL 5, but that conditional does
# not exist in all versions of cmake.
if(CMAKE_SYSTEM_VERSION VERSION_GREATER 4.99)

    list(APPEND PSP_TARGET_MODULE_LIST rtems_sysmon)

endif()

# Selecting the network module based on platform being used
# For Qemu RTEMS versions 4.11,5,6
if(RTEMS_BSP MATCHES "pc686")
    list(APPEND PSP_TARGET_MODULE_LIST network_pc686_rtems)
endif()