add_cfe_coverage_stubs(iodriver
    iodriver_base_stubs.c
    iodriver_impl_stubs.c
)

#target_compile_definitions(coverage-iodriver-stubs PRIVATE
#    _CFE_PSP_MODULE_
#)
#target_include_directories(coverage-iodriver-stubs PUBLIC
#    $<TARGET_PROPERTY:iodriver,INTERFACE_INCLUDE_DIRECTORIES>
#)
#target_link_libraries(coverage-iodriver-stubs PRIVATE
#    psp_module_api
#    ut_assert
#)
