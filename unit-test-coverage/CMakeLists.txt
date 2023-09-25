######################################################################
#
# CMAKE build recipe for PSP white-box coverage tests
#
######################################################################

# The following cache variables are recognized:
#   PSPCOVERAGE_TARGETS  -> the intended PSP module(s) that run on the actual target
#
# Like OSAL coverage testing, the actual underlying OS calls are stubbed out, there
# is no dependency on the actual underlying OS.  All coverage tests can be built on
# all platforms regardless of the actual PSP in use for flight software.

project(PSPCOVERAGE C)

set(PSPCOVERAGE_TARGETS mcp750-vxworks pc-rtems CACHE STRING "PSP target(s) to build coverage tests for (default=all)")

# Check that coverage has been implemented for this PSPTYPE
foreach(PSPTYPE ${PSPCOVERAGE_TARGETS})
    if (NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PSPTYPE})
      message(FATAL_ERROR "No coverage tests implemented for ${PSPTYPE}")
    endif ()
endforeach()

message(STATUS "PSP Coverage Test Targets: ${PSPCOVERAGE_TARGETS}")

# Utilize the shared UT assert library, along with the standard OSAL includes
include_directories(${UT_ASSERT_SOURCE_DIR}/inc)
include_directories(${PSPCOVERAGE_SOURCE_DIR}/ut-stubs/inc)

add_subdirectory(ut-stubs)
add_subdirectory(modules)

# Build targets for each of the indicated PSPs
foreach(SETNAME ${PSPCOVERAGE_TARGETS})
    add_subdirectory(${SETNAME})
endforeach()

