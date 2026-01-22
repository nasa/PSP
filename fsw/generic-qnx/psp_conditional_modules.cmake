# Selecting the backtrace module based on QNX SDP version being used
if (QNX_SDP_VERSION EQUAL 800)
    list(APPEND PSP_TARGET_MODULE_LIST backtrace_libunwind)
elseif (QNX_SDP_VERSION EQUAL 710) 
    list(APPEND PSP_TARGET_MODULE_LIST backtrace_qnx)
endif()
