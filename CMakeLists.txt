######################################################################
#
# CMAKE build recipe for CFE Platform Support Package (PSP)
#
######################################################################

project(CFEPSP C)

if (NOT CFE_SYSTEM_PSPNAME)
  message(FATAL_ERROR "CFE_SYSTEM_PSPNAME is not defined - do not know which to build")
endif()

set(CFE_PSP_TARGETNAME "${CFE_SYSTEM_PSPNAME}")
add_definitions(-D_CFE_PSP_)       # macro to indicate PSP scope

# The "psp_module_api" defines the interface between internal PSP components
add_library(psp_module_api INTERFACE)
target_compile_definitions(psp_module_api INTERFACE
    $<TARGET_PROPERTY:osal,INTERFACE_COMPILE_DEFINITIONS> # use defs from OSAL
)
target_include_directories(psp_module_api INTERFACE
    fsw/inc         # public API
    fsw/shared/inc  # all PSP shared headers
    fsw/${CFE_PSP_TARGETNAME}/inc # all impl headers
    ${CFE_SOURCE_DIR}/cmake/target/inc    # for sysconfig
    $<TARGET_PROPERTY:osal,INTERFACE_INCLUDE_DIRECTORIES>  # use headers from OSAL
)


# The PSP is currently built in two parts, consisting of a fully platform-specific
# module combined with a shared component which is built for multiple targets.
# The "shared" component is compiled using headers from the platform-specific module
# so it is still ultimately a platform-specific binary, and it all gets wrapped into
# a single PSP static library target.
add_subdirectory(fsw/${CFE_PSP_TARGETNAME} ${CFE_PSP_TARGETNAME}-impl)
add_subdirectory(fsw/shared ${CFE_PSP_TARGETNAME}-shared)

add_library(psp-${CFE_PSP_TARGETNAME} STATIC
    $<TARGET_OBJECTS:psp-${CFE_PSP_TARGETNAME}-shared>
    $<TARGET_OBJECTS:psp-${CFE_PSP_TARGETNAME}-impl>
)

target_include_directories(psp-${CFE_PSP_TARGETNAME} INTERFACE 
    fsw/inc
)


if (ENABLE_UNIT_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ut-stubs)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/unit-test-coverage)
endif (ENABLE_UNIT_TESTS)

