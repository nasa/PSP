# This indicates where to install target binaries created during the build
set(INSTALL_SUBDIR "cf")

message(STATUS "WIND_BASE IS $ENV{WIND_BASE}")

##
## Target Defines for the OS, Hardware Arch, etc..
##
#add_definitions("-DVOLTAB_PATH=\"/ram0/cf\"")
#add_definitions("-D_VXWORKS_OS_ -D_HAVE_STDINT_ -D_PPC_ -D__PPC__ -D_EMBED_ -DTOOL_FAMILY=gnu -DTOOL=e500v2gnu -D_WRS_KERNEL -DCPU=PPC85XX -DCPU_VARIANT=_ppc85xx_e500v2 \"-D_VSB_CONFIG_FILE=<../lib/h/config/vsbConfig.h>\"")


## 
## Endian Defines
##
add_definitions(-D_EB -DENDIAN=_EB -DSOFTWARE_BIG_BIT_ORDER) 

##
## Compiler Architecture Switches
##
#add_definitions("-mcpu=8548 -te500v2 -mstrict-align -fno-builtin -fvolatile -mhard-float -fno-implicit-fp -mfloat-gprs=double -mspe=yes -mabi=spe -mlongcall")

#include_directories($ENV{WIND_BASE}/target/h/wrn/coreip)
#include_directories($ENV{WIND_BASE}/target/3rdparty/aitech/sp0)
#include_directories($ENV{WIND_BASE}/target/config/sp0)
