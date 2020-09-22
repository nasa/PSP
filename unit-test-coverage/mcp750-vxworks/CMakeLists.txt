######################################################################
#
# CMAKE build recipe for mcp750-vxworks PSP white-box coverage tests
#
######################################################################

include_directories("${CFEPSP_SOURCE_DIR}/fsw/mcp750-vxworks/inc")
include_directories("${PSPCOVERAGE_SOURCE_DIR}/shared/inc")

# The target names will be the PSP name with a "ut" prefix
# this is to distinguish these test targets from the FSW targets.
set(CFE_PSP_TARGETNAME "ut-${SETNAME}")
add_subdirectory("${CFEPSP_SOURCE_DIR}/fsw/${SETNAME}" "${CFE_PSP_TARGETNAME}-impl")
add_subdirectory("${CFEPSP_SOURCE_DIR}/fsw/shared" "${CFE_PSP_TARGETNAME}-shared")
add_subdirectory(adaptors)

# as UT assert defines OS_Application_Startup and OS_Application_Run, we need
# to change the ones in this module to a different name.
target_compile_definitions(psp-${CFE_PSP_TARGETNAME}-impl PRIVATE
    OS_Application_Startup=UT_OS_Application_Startup
    OS_Application_Run=UT_OS_Application_Run
)

# only the actual FSW src file gets the coverage instrumentation
target_compile_options(psp-${CFE_PSP_TARGETNAME}-impl PRIVATE
    ${UT_COVERAGE_COMPILE_FLAGS}
)
target_compile_options(psp-${CFE_PSP_TARGETNAME}-shared PRIVATE
    ${UT_COVERAGE_COMPILE_FLAGS}
)

# both the FSW src file and the adaptor file get compiled with override includes
target_include_directories(psp-${CFE_PSP_TARGETNAME}-impl BEFORE PRIVATE
    ${PSPCOVERAGE_SOURCE_DIR}/ut-stubs/override_inc
)
target_include_directories(psp-${CFE_PSP_TARGETNAME}-shared BEFORE PRIVATE
    ${PSPCOVERAGE_SOURCE_DIR}/ut-stubs/override_inc
)

add_executable(coverage-${CFE_PSP_TARGETNAME}-testrunner
    src/coveragetest-psp-mcp750-vxworks.c
    src/coveragetest-cfe-psp-start.c
    src/coveragetest-cfe-psp-support.c
    ${PSPCOVERAGE_SOURCE_DIR}/shared/src/coveragetest-cfe-psp-exceptionstorage.c
    $<TARGET_OBJECTS:psp-${CFE_PSP_TARGETNAME}-shared>
    $<TARGET_OBJECTS:psp-${CFE_PSP_TARGETNAME}-impl>
)

target_link_libraries(coverage-${CFE_PSP_TARGETNAME}-testrunner
    ${UT_COVERAGE_LINK_FLAGS}
    ut-adaptor-${CFE_PSP_TARGETNAME}
    ut_psp_cfe_stubs
    ut_psp_libc_stubs
    ut_osapi_stubs
    ut_assert
)

add_test(coverage-${CFE_PSP_TARGETNAME} coverage-${CFE_PSP_TARGETNAME}-testrunner)

foreach(TGT ${INSTALL_TARGET_LIST})
    install(TARGETS coverage-${CFE_PSP_TARGETNAME}-testrunner DESTINATION ${TGT}/${UT_INSTALL_SUBDIR})
endforeach()

