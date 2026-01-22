######################################################################
#
# CMAKE build recipe for tests of Endianness conversions
# This contains a functional test not just a coverage test
#
add_definitions(-D_CFE_PSP_MODULE_)
add_definitions(-D_UNIT_TEST_)

# Also link this with the real (non-stub) endian API
set (UT_COVERAGE_LINK_FLAGS endian_api ${UT_COVERAGE_LINK_FLAGS})

add_psp_covtest(endian_api coveragetest-endian_api.c
    ${CFEPSP_SOURCE_DIR}/fsw/modules/endian_api/cfe_psp_endian_common.c
    ${CFEPSP_SOURCE_DIR}/fsw/modules/endian_api/cfe_psp_endian_wrappers.c
    ${CFEPSP_SOURCE_DIR}/fsw/modules/endian_api/cfe_psp_endian_generic.c
)
