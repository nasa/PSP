# The sysmon module only works in RTEMS >= 5.
# Ideally this check should be VERSION_GREATER_EQUAL 5, but that conditional does
# not exist in all versions of cmake.
if(CMAKE_SYSTEM_VERSION VERSION_GREATER 4.99)

    list(APPEND PSP_TARGET_MODULE_LIST rtems_sysmon)

endif()