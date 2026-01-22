# Generic VxWorks 7 Downloadable Kernel Mode (DKM) Platform Support Package

This document is intended to describe what is needed to run cFS on VxWorks 7 in kernel mode, but it is not intended to be a complete guide to building and running the VxWorks image on a target. The goal is to have enough information to build the neccesary VxWorks kernel image and should include:
- VxWorks features that are needed by the cFS (TBD).
- Information about the cfeSupport.c module in the bsp-integration directory.
- How the ROMFS is used to store the cFS runtime files.
- Work to do/improvements

# Assumptions:

* The vxworks OSAL and generic-vxworks OSAL BSP are used.
* The cFE repository has the necessary CMake toolchain files for VxWorks DKM targets.
* A Compatible VxWorks 7 installation is available. This was tested on VxWorks 7 23.09 for the Raspberry Pi 4 and VxWorks 7 23.09 for the vxsim target. The public VxWorks SDKs may work with some modifications to work around features that were not included in the Public VxWorks SDK kernel.

The cFS project developers have a **vxworks_support** repository available that includes VxWorks VSB and VIP configurations, scripts, and documentation to support cFS development on VxWorks.

# How to build cFS for VxWorks 7 Kernel Mode (Version 23.09) 

These are general guidelines for being able to build the cFS with this PSP in order to run it on a generic VxWorks 7 target.

## Install VxWorks 7 and be able to run on the selected target

The first step (that is not covered here) is to have a working VxWorks 7 installation and be able to build and run the VxWorks kernel on your target board. At the time this guide was written, the cFS developers used VxWorks 7 23.09 and a Raspberry Pi 4 (Aarch64) target board. Before building the cFS, you should be able to:
- Build a VxWorks Source Build (VSB) project
- Configure and build a VxWorks Image Project (VIP) for your target platform
- Verify that you can run a VxWorks kernel image on the target platform.

The cFS requires certain features in the VxWorks kernel. At a minimum the kernel configuration that was used for development will be listed in a file in the *doc* directory. Note that this configuration may have extra options that are not necessarily required by the cFS.  

## Add the cfeSupport.c file to the VIP project

In order to have the cFE core load without unresolved symbols, you need to add the cfeSupport.c file to the VIP. This can be done by doing the following steps:
- Copy the src/bsp-integration/cfeSupport.c file to the VxWorks VIP project directory
- In the VIP directory, run the command: 
```
vip$ vxprj vip file add cfeSupport.c
```
- Still in the VIP directory, rebuild the VIP
```
vip$ vxprj vip build
```

## Configure and Build the cFS for VxWorks 7 Raspberry Pi 4

* Clone the correct branch of the cFS that supports VxWorks 7 and this generic-vxworks-dkm PSP 
* Update/clone the submodules: 
```
git submodule update --init --recursive
```
* Copy the cfe/cmake/sample_defs directory to the top level directory of the cfs repo:
```
cp -a cfe/cmake/sample_defs .
```
* Copy cfe/cmake/Makefile.sample to Makefile in the top level directory of the cfs repo:
```
cp cfe/cmake/sample_defs/Makefile.sample Makefile
```
* In the sample_defs directory, edit **targets.cmake** and change the **cpu1_SYSTEM** macro to **aarch64-vx7dkm**. Note that this should match the name of the toolchain file you are using. In this case the toolchain file is **toolchain-aarch64-vx7dkm.cmake**. This architecture name will be different for other targets.
```
SET(cpu1_PROCESSORID 1)
SET(cpu1_APPLIST ci_lab to_lab sch_lab)
SET(cpu1_FILELIST cfe_es_startup.scr)
SET(cpu1_SYSTEM aarch64-vx7dkm)
```

* Also in the sample_defs directory, edit the **arch_build_custom.cmake** file. Currently there are several lines that need to be commented out due to differences in the compiler that is used in the VxWorks SDK. Comment out the following lines: -Werror, -Wno-format-truncation, and -Wno-stringop-truncation.
```
add_compile_options(
    -std=c99                    # Target the C99 standard (without gcc extensions)
    -pedantic                   # Issue all the warnings demanded by strict ISO C
    -Wall                       # Warn about most questionable operations
    -Wstrict-prototypes         # Warn about missing prototypes
    -Wwrite-strings             # Warn if not treating string literals as "const"
    -Wpointer-arith             # Warn about suspicious pointer operations
    #-Werror                     # Warnings are caused by Clang compiler 
    #-Wno-format-truncation      # Inhibit printf-style format truncation warnings - Not in Clang
    #-Wno-stringop-truncation    # Inhibit string operation truncation warnings - Not in Clang
)
```
Now the cFS should be ready to build for VxWorks 7 

## Build the cFS for your target 

> [!NOTE]
> It is assumed that the cfs is cloned to ~/cfs and the VxWorks environment setup script has been run to setup the VxWorks compiler and development tools. The cFS development team uses the scripts in the vxworks_support repository to do this.

Switch to the cFS directory that has been setup and run the make steps:
```
$ cd ~/cfs 
$ make distclean
$ make prep
$ make
$ make install
```

If the build completes successfully, the cFS binaries, startup script, and tables will be in:
```
build/exe/cpu1
```

## Copy the cFS runtime files to the VIP project 'romfs' directory

Copy the **cfs/build/exe/cpu1** directory to the VIP project 'romfs' directory and rebuild the VIP project to include these files.
Note that to make this generic-vxworks-dkm work on multiple platforms, including some that may not have a configured non-volatile disk, the ROMFS feature is used to store the cFS runtime files. The cFS runtime files could be stored on a target resident file system. To use a different volume to store the cFS runtime files, you must change the folloing OSAL call in cfe_psp_start.c:
```
    Status = OS_FileSysAddFixedMap(&fs_id, "/romfs/cpu1/cf", "/cf");
```
The line of code above is how the cFS path "/cf" that is in the startup script and cFS configuration files gets mapped to the target file system. It will need to be changed for a different file system, cFS configuration, etc.

## Boot the VxWorks Image and run the cFS

The instructions to boot the image are target specific, but the goal is to boot the system and obtain a VxWorks kernel command shell.
Once this shell is working and the cFS runtime files are in the /romfs/cpu1 directory you can start the cFS with the following command:

```
-> cd "/romfs/cpu1"
-> startCfeCore /romfs/cpu1/core-cpu1.exe 
```

Note that the path above is the default, so if that is unchanged the following will work:
```
-> startCfeCore
```

You should see the cFS load and start the services and apps.

# Work to do / future improvements

In VxWorks 7, the cFS and other kernel tasks run in virtual memory space managed by VxWorks. Because of this, all memory and addressable I/O is not immediately addessable. For example, in order to access peripheral registers on a UART device, the register set must be mapped into virtual address space using the pmapGlobalMap function. Because of this, the modules in the PSP used to access memory and I/O space will be limited to what is mapped into virtual address space.

Future improvements will include PSP modules that can be used to map additional memory and I/O space for VxWorks 7 DKM applications.
