add_library(ut_psp-${CFE_PSP_TARGETNAME}_stubs ut_psp_stubs.c)
target_link_libraries(ut_psp-${CFE_PSP_TARGETNAME}_stubs PRIVATE 
    psp_module_api
    ut_assert 
)
