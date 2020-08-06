###############################################################################
## compiler-opts.mak - compiler definitions and options for building the cFE 
##
## Target: PPC AiTech SP0 (Freescale 8548, e500 core) COTS board with vxWorks 6.x
###############################################################################

## 
## Warning Level Configuration
##
## WARNINGS =-Wall -ansi -pedantic -Wstrict-prototypes
WARNINGS = -Wall

##
## A fix for Windows systems on vxWorks 6.4
## When generating dependancies, the Windows GCC cannot seem to deal
## with the Windows style path separators in the WIND_BASE macro.
##
FIXED_WIND_BASE = $(subst \,/,$(WIND_BASE))

##
## vxWorks system includes 
##
VXINCDIR = $(FIXED_WIND_BASE)/target/h \
$(FIXED_WIND_BASE)/target/h/wrn/coreip \
$(FIXED_WIND_BASE)/target/h/drv \
$(FIXED_WIND_BASE)/target/src/config \
$(FIXED_WIND_BASE)/target/src/drv \
$(FIXED_WIND_BASE)/target/config/comps/src \
$(FIXED_WIND_BASE)/target/config/comps/src/dosfs2 \

SYSINCS = $(VXINCDIR:%=-I%)

##
## Target Defines for the OS, Hardware Arch, etc..
##
TARGET_DEFS += -D_VXWORKS_OS_ -D_PPC_ -D__PPC__  $(CFE_SB_NET) -D$(OS) -D_EMBED_ \
	           -DTOOL_FAMILY=gnu -DTOOL=e500v2gnu -D_WRS_KERNEL -DCPU=PPC85XX \
	           -DCPU_VARIANT=_ppc85xx_e500v2 \
	           "-D_VSB_CONFIG_FILE=<../lib/h/config/vsbConfig.h>"

## 
## Endian Defines
##
ENDIAN_DEFS = -D_EB -DENDIAN=_EB -DSOFTWARE_BIG_BIT_ORDER 

##
## Compiler Architecture Switches
##
ARCH_OPTS = -gstatement-frontiers -mcpu=e500mc -D_WRS_HARDWARE_FP -mabi=elfv2 -mcmodel=medium -fstrength-reduce \
			-mtls-size=16 -mhard-float -D__ppc -D__ppc__ -m64 -D__ppc64__ -mstrict-align -std=c11 -D__vxworks \
			-D__VXWORKS__ -D__ELF__ -D_HAVE_TOOL_XTORS -ftls-model=local-exec -fno-zero-initialized-in-bss \
			-fno-builtin -fno-strict-aliasing -D_USE_INIT_ARRAY -Wall -Wconversion -Wno-sign-conversion -MD -MP \
			-mlongcall -DCPU=_VX_PPCE500MC -DTOOL_FAMILY=gnu -DTOOL=gnu -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP \
			-D_VSB_CONFIG_FILE="/home/darkwing/work/nasa/582/cfs_5545/workspace/hello2/../vsb_5020/h/config/vsbConfig.h"
            
##
## Application specific compiler switches 
##
ifeq ($(BUILD_TYPE),CFE_APP)
   APP_COPTS  = -mlongcall  
   APP_ASOPTS =
else
   APP_COPTS  =  
   APP_ASOPTS =
endif

##
## Extra Cflags for Assembly listings, etc.
##
LIST_OPTS = -Wa,-a=$*.lis 

##
## gcc options for dependancy generation
##
COPTS_D = $(APP_COPTS) $(ENDIAN_DEFS) $(TARGET_DEFS) $(ARCH_OPTS) $(SYSINCS) $(WARNINGS)

## 
## General gcc options that apply to compiling and dependency generation.
##
COPTS = $(LIST_OPTS) $(COPTS_D)

##
## Extra defines and switches for assembly code
##
ASOPTS = $(APP_ASOPTS) -P -xassembler-with-cpp 

##---------------------------------------------------------
## Application file extention type
## This is the defined application extention.
## Known extentions: Mac OS X: .bundle, Linux: .so, 
##                   RTEMS: .s3r, vxWorks: .o etc.. 
##---------------------------------------------------------
APP_EXT = o

####################################################
## Host Development System and Toolchain definitions
##
## Host OS utils
##
RM = rm -f
CP = cp

##
## Compiler tools
##
COMPILER = ccppc
ASSEMBLER = ccppc
LINKER = ldppc
AR = arppc
NM = nmppc
OBJCPY = objcopyppc
TABLE_BIN = elf2cfetbl


