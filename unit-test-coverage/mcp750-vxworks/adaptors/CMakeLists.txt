# "Adaptors" help enable the unit test code to reach functions/objects that
# are otherwise not exposed.  

# NOTE: These source files are compiled with OVERRIDES on the headers just like
# the FSW code is compiled.  This is how it is able to include internal headers
# which otherwise would fail.  But that also means that adaptor code cannot call
# any library functions, as this would also reach a stub, not the real function.

add_library(ut-adaptor-${CFE_PSP_TARGETNAME} STATIC
    src/ut-adaptor-bootrec.c
    ${PSPCOVERAGE_SOURCE_DIR}/shared/adaptors/src/ut-adaptor-exceptions.c
)

# the "override_inc" dir contains replacement versions of the C-library include files.
target_include_directories(ut-adaptor-${CFE_PSP_TARGETNAME} BEFORE PRIVATE
    ${PSPCOVERAGE_SOURCE_DIR}/ut-stubs/override_inc
)

target_include_directories(ut-adaptor-${CFE_PSP_TARGETNAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${PSPCOVERAGE_SOURCE_DIR}/shared/adaptors/inc
)

target_link_libraries(ut-adaptor-${CFE_PSP_TARGETNAME} PRIVATE 
    psp_module_api
    ut_assert 
)
