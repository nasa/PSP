include_directories(inc)

add_library(psp-${CFE_PSP_TARGETNAME}-impl OBJECT
	src/cfe_psp_timer.c
	src/cfe_psp_support.c
)
