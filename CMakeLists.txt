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

# Read the default compile-time configuration, and update with
# any mission/project specific options in the PSP_CONFIGURATION_FILE
include("${CFEPSP_SOURCE_DIR}/default_config.cmake")

# The user-specified file is optional, but in case the value is defined but the
# file does not exist, this should be treated as an error.
foreach(CONFIG ${PSP_CONFIGURATION_FILE})
    include(${CONFIG})
endforeach(CONFIG PSP_CONFIGURATION_FILE)

# Use the supplied configuration to generate the pspconfig.h file
# which can be referenced by the code.  This will be stored in the top level
# "inc" directory of the binary output directory
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/inc")
configure_file(
    "${CFEPSP_SOURCE_DIR}/pspconfig.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/pspconfig.gen"
    @ONLY
)

# Only copy the pspconfig.h into place if different from the existing file
# This avoids unnecessarily rebuilding all code in case cmake was re-run
# and but generated the same file.
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_BINARY_DIR}/pspconfig.gen"
    "${CMAKE_CURRENT_BINARY_DIR}/inc/pspconfig.h"
)

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
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/inc>  # for pspconfig.h
    $<TARGET_PROPERTY:osal,INTERFACE_INCLUDE_DIRECTORIES>  # use headers from OSAL
)

# Include definition of cfe_psp_backtrace.h referenced by cfe_psp_config.h for QNX PSP
if (QNX_SDP_VERSION EQUAL 800)
    target_include_directories(psp_module_api INTERFACE $<TARGET_PROPERTY:backtrace_libunwind,INTERFACE_INCLUDE_DIRECTORIES>)
elseif (QNX_SDP_VERSION EQUAL 710) 
    target_include_directories(psp_module_api INTERFACE $<TARGET_PROPERTY:backtrace_qnx,INTERFACE_INCLUDE_DIRECTORIES>)
endif()

# Translate the CFE_PSP_TARGETNAME to a set of additional modules to build
file(STRINGS "${CMAKE_CURRENT_LIST_DIR}/fsw/${CFE_PSP_TARGETNAME}/psp_module_list.cmake" PSP_TARGET_MODULE_LIST REGEX "^[a-zA-Z]")
include("${CMAKE_CURRENT_LIST_DIR}/fsw/${CFE_PSP_TARGETNAME}/psp_conditional_modules.cmake" OPTIONAL)

# The PSP is currently built in modular parts, consisting of a platform-specific
# module(s) combined with a shared component which is built for multiple targets.
# The "shared" component is compiled using headers from the platform-specific module
# so it is still ultimately a platform-specific binary, and it all gets wrapped into
# a single PSP static library target.
add_subdirectory(fsw/${CFE_PSP_TARGETNAME} ${CFE_PSP_TARGETNAME}-impl)
add_subdirectory(fsw/shared ${CFE_PSP_TARGETNAME}-shared)

# Generate a list of PSP modules along with a pointer to its API structure/entry point
set(GENERATED_EXTERNS)
set(GENERATED_KEYVALS)
foreach(PSPMOD ${PSP_TARGET_MODULE_LIST})
    add_subdirectory(fsw/modules/${PSPMOD} ${PSPMOD}-${CFE_PSP_TARGETNAME}-impl)
    list(APPEND GENERATED_EXTERNS "extern CFE_PSP_ModuleApi_t CFE_PSP_${PSPMOD}_API\;\n")
    list(APPEND GENERATED_KEYVALS "{ .Name = \"${PSPMOD}\", .Api = &CFE_PSP_${PSPMOD}_API },\n")
endforeach()

string(CONCAT GENERATED_EXTERNS ${GENERATED_EXTERNS})
string(CONCAT GENERATED_KEYVALS ${GENERATED_KEYVALS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/module_list.c.in ${CMAKE_CURRENT_BINARY_DIR}/${CFE_PSP_TARGETNAME}_module_list.c @ONLY)

add_library(psp-${CFE_PSP_TARGETNAME} STATIC
    ${CMAKE_CURRENT_BINARY_DIR}/${CFE_PSP_TARGETNAME}_module_list.c
    $<TARGET_OBJECTS:psp-${CFE_PSP_TARGETNAME}-shared>
    $<TARGET_OBJECTS:psp-${CFE_PSP_TARGETNAME}-impl>
)
target_link_libraries(psp-${CFE_PSP_TARGETNAME} PUBLIC
    ${PSP_TARGET_MODULE_LIST}
)
target_link_libraries(psp-${CFE_PSP_TARGETNAME} PRIVATE
    psp_module_api
)

target_include_directories(psp-${CFE_PSP_TARGETNAME} INTERFACE
    fsw/inc
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/inc>  # for pspconfig.h
)


if (ENABLE_UNIT_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ut-stubs)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/unit-test-coverage)
endif ()
