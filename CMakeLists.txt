project(CFEPSP C)

if (NOT CFE_SYSTEM_PSPNAME)
  message(FATAL_ERROR "CFE_SYSTEM_PSPNAME is not defined - do not know which to build")
endif()

if (NOT CFE_SYSTEM_PSPPATH)
  set(CFE_SYSTEM_PSPPATH ${CMAKE_CURRENT_SOURCE_DIR}/fsw/${CFE_SYSTEM_PSPNAME})
endif()

if (NOT IS_DIRECTORY ${CFE_SYSTEM_PSPPATH})
  message(FATAL_ERROR "PSP ${CFE_SYSTEM_PSPNAME} could not be found at path ${CFE_SYSTEM_PSPPATH}")
endif()

add_definitions(-D_CFE_PSP_)
include_directories(${CFE_SYSTEM_PSPPATH}/inc)
include_directories(fsw/shared)

# Use all source files under the shared code directory (always)
# as well as all the files for the selected PSP
set(PSPFILES)
aux_source_directory(fsw/shared PSPFILES)
aux_source_directory(${CFE_SYSTEM_PSPPATH}/src PSPFILES)

add_library(psp-${CFE_SYSTEM_PSPNAME} STATIC ${PSPFILES})

if (ENABLE_UNIT_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fsw/ut-stubs)
endif (ENABLE_UNIT_TESTS)
