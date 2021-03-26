######################################################################
#
# CMAKE build recipe for PSP modules white-box coverage tests
#
######################################################################

include_directories("${PSPCOVERAGE_SOURCE_DIR}/shared/inc")
include_directories("${PSPCOVERAGE_SOURCE_DIR}/modules/inc")

# redefine the add_psp_module to make a unit test variant
# this needs to name the target differently, so it doesn't conflict with the FSW target.
# this is similar to add_cfe_coverage_test() on the CFE side, but the set of interfaces
# and link libraries is different from that of a CFS app
function(add_psp_module MODULE_NAME)

    set(TEST_NAME "coverage-pspmod-${MODULE_NAME}")
    set(OBJECT_TARGET "${TEST_NAME}-object")
    set(RUNNER_TARGET "${TEST_NAME}-testrunner")
    # Create the module

    add_library(${OBJECT_TARGET} OBJECT ${ARGN})

    target_compile_options(${OBJECT_TARGET} PRIVATE
        ${UT_COVERAGE_COMPILE_FLAGS}
    )
    target_include_directories(${OBJECT_TARGET} PRIVATE
        ${PSPCOVERAGE_SOURCE_DIR}/ut-stubs/override_inc # overrides for system headers
        ${CFEPSP_SOURCE_DIR}/fsw/inc                    # PSP public API
        ${CFEPSP_SOURCE_DIR}/fsw/shared/inc             # all PSP shared headers
        ${CFE_SOURCE_DIR}/cmake/target/inc              # for sysconfig headers
        $<TARGET_PROPERTY:osal,INTERFACE_INCLUDE_DIRECTORIES>  # use headers from OSAL
    )

    # Compile a test runner application, which contains the
    # actual coverage test code (test cases) and the unit under test
    add_executable(${RUNNER_TARGET}
        ${PSPCOVERAGE_SOURCE_DIR}/modules/src/coveragetest-${MODULE_NAME}.c
        $<TARGET_OBJECTS:${OBJECT_TARGET}>
    )

    # This also needs to be linked with UT_COVERAGE_LINK_FLAGS (for coverage)
    # This is also linked with any other stub libraries needed,
    # as well as the UT assert framework
    target_link_libraries(${RUNNER_TARGET}
        ${UT_COVERAGE_LINK_FLAGS}
        psp_module_api
        ut_psp_libc_stubs
        ut_osapi_stubs
        ut_assert
    )

    add_test(${TEST_NAME} ${RUNNER_TARGET})
    foreach(TGT ${INSTALL_TARGET_LIST})
        install(TARGETS ${RUNNER_TARGET} DESTINATION ${TGT}/${UT_INSTALL_SUBDIR})
    endforeach()

endfunction(add_psp_module)

# a list of modules for which there is a coverage test implemented
set(UT_PSPMODLIST
    timebase_vxworks
)

foreach(UT_PSPMOD ${UT_PSPMODLIST})
    add_subdirectory(${CFEPSP_SOURCE_DIR}/fsw/modules/${UT_PSPMOD} ${UT_PSPMOD})
endforeach()

