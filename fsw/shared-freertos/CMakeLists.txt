
######################################################################
#
# CMAKE build recipe for FreeRTOS PSP component
#
######################################################################

# This contains the fully platform-specific code to
# run CFE on this target.

message("*** Inside cmake list ${CMAKE_CURRENT_LIST_FILE}.")
message("*** Using OSAL_FREERTOS_SRC_DIR '${OSAL_FREERTOS_SRC_DIR}'.")
message("*** Using OSAL_FREERTOS_INC_DIR '${OSAL_FREERTOS_INC_DIR}'.")


add_library(psp-${CFE_PSP_TARGETNAME}-impl OBJECT
    src/cfe_psp_memory.c
    src/cfe_psp_start.c
    src/cfe_psp_timer.c
    vendor/cfe_psp_console.c
    vendor/cfe_psp_memory.c
    vendor/cfe_psp_memtab.c
    todo/cfe_psp_exception.c
    todo/cfe_psp_memory.c
    todo/cfe_psp_support.c
    todo/cfe_psp_timer.c
)

target_compile_definitions(psp-${CFE_SYSTEM_PSPNAME}-impl PRIVATE
    $<TARGET_PROPERTY:psp_module_api,INTERFACE_COMPILE_DEFINITIONS>
)

target_include_directories(psp-${CFE_PSP_TARGETNAME}-impl PRIVATE
    inc
    $<TARGET_PROPERTY:psp_module_api,INTERFACE_INCLUDE_DIRECTORIES>
)
