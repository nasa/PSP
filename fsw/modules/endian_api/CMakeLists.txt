
# Check if the target system provides the "endian.h" header file.
# This needs to use the same compile definitions as OSAL when testing, BUT
# in typical CMake fashion things are not consistent.  The interface
# compile definitions is a simple list whereas the COMPILE_DEFINITIONS passed
# to try_compile needs to have a -D in front of every option like add_definitions()
get_property(OSAL_COMPILE_DEFS TARGET osal_public_api PROPERTY INTERFACE_COMPILE_DEFINITIONS)

# When using glibc it may also be hidden behind one of these feature flags
set(PSP_ENDIAN_TRY_COMPILE_DEFS -D_DEFAULT_SOURCE -D_BSD_SOURCE)
foreach(DEF ${OSAL_COMPILE_DEFS})
    list(APPEND PSP_ENDIAN_TRY_COMPILE_DEFS "-D${DEF}")
endforeach()

add_definitions(${PSP_ENDIAN_TRY_COMPILE_DEFS})

# Check if the system provides an endian.h and if it is usable
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
try_compile(PSP_HAVE_ENDIAN_H
    ${CMAKE_CURRENT_BINARY_DIR}/configtest_endian_h
    ${CMAKE_CURRENT_SOURCE_DIR}/configtest_endian_h.c
    COMPILE_DEFINITIONS ${PSP_ENDIAN_TRY_COMPILE_DEFS} # use defs from OSAL
)

if ($ENV{VERBOSE})
    message(STATUS "HAVE_ENDIAN_H=${PSP_HAVE_ENDIAN_H}")
endif()

if (PSP_HAVE_ENDIAN_H)
    # Use the endian.h variant, this is likely to be better optimized
    set(PSP_ENDIAN_SOURCE cfe_psp_endian_wrappers.c)
else()
    # Use the generic variant, this is not optimized but works anywhere
    set(PSP_ENDIAN_SOURCE cfe_psp_endian_generic.c)
endif()

add_psp_module(endian_api cfe_psp_endian_common.c ${PSP_ENDIAN_SOURCE})
