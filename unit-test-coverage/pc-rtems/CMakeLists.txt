######################################################################
#
# CMake build recipe for pc-rtems PSP white-box coverage tests
#
######################################################################

include_directories(${CFEPSP_SOURCE_DIR}/fsw/pc-rtems/inc)
include_directories(${PSPCOVERAGE_SOURCE_DIR}/shared/inc)

# Target names use a "ut" prefix to avoid confusion with the FSW targets
set(CFE_PSP_TARGETNAME "ut-${SETNAME}")
add_subdirectory(${CFEPSP_SOURCE_DIR}/fsw/${SETNAME} ${CFE_PSP_TARGETNAME}-impl)
add_subdirectory(${CFEPSP_SOURCE_DIR}/fsw/shared ${CFE_PSP_TARGETNAME}-shared)

# The UT assert library defines OS_Application_Startup, so this redefines ours with a "UT_" prefix
target_compile_definitions(psp-${CFE_PSP_TARGETNAME}-impl PRIVATE
    OS_Application_Startup=UT_OS_Application_Startup
)

foreach(TGT psp-${CFE_PSP_TARGETNAME}-impl psp-${CFE_PSP_TARGETNAME}-shared)
    target_compile_options(${TGT} PRIVATE ${UT_COVERAGE_COMPILE_FLAGS})
    target_include_directories(${TGT} BEFORE PRIVATE ${PSPCOVERAGE_SOURCE_DIR}/ut-stubs/override_inc)
endforeach()

add_executable(coverage-${CFE_PSP_TARGETNAME}-testrunner
    src/coveragetest-cfe-psp-exception.c
    src/coveragetest-cfe-psp-memory.c
    src/coveragetest-cfe-psp-ssr.c
    src/coveragetest-cfe-psp-start.c
    src/coveragetest-cfe-psp-support.c
    src/coveragetest-cfe-psp-watchdog.c
    src/coveragetest-psp-pc-rtems.c
    $<TARGET_OBJECTS:psp-${CFE_PSP_TARGETNAME}-shared>
    $<TARGET_OBJECTS:psp-${CFE_PSP_TARGETNAME}-impl>
)

target_link_libraries(coverage-${CFE_PSP_TARGETNAME}-testrunner PUBLIC
    ${UT_COVERAGE_LINK_FLAGS}
    psp_module_api
    ut_psp_cfe_stubs
    ut_psp_libc_stubs
    ut_osapi_stubs
    ut_assert
)

add_test(coverage-${CFE_PSP_TARGETNAME} coverage-${CFE_PSP_TARGETNAME}-testrunner)

foreach(TGT ${INSTALL_TARGET_LIST})
    install(TARGETS coverage-${CFE_PSP_TARGETNAME}-testrunner DESTINATION ${TGT}/${UT_INSTALL_SUBDIR})
endforeach()
