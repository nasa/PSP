ABOUT THE PC-RTEMS CFE PSP for RTEMS 5
========================================

Note: These instructions are for RTEMS 5 

The "pc-rtems" PSP layer is intended to be an easy way to prove out the basic functionality
of CFE running on RTEMS without actually requiring a real hardware target with RTEMS support.  

It is based on:
    - RTEMS built using the "pc686" BSP (i.e. an ordinary off the shelf i686 PC)
    - Running the resulting binary in a QEMU virtual i686 PC
    
The example instructions here are to set up RTEMS under your local home dir in ${HOME}/rtems-5.
However any location can be used e.g. /opt/x-tools/rtems-5 might be good choice on a shared
build system.  The RTEMS_BSP_TOP directory must be set to the same location either by editing
the example toolchain file or via -D options to the CMake build.
 

I. Setting up and compiling RTEMS BSP

1) install RTEMS toolchain for i386-rtems5 (or relevant target arch) into ${HOME}/rtems5

The RTEMS official docs have instructions for this, which should supercede anything here.

Basic use of the the "rtems source builder" tool which works at the time of this writing:
OFFICIAL RTEMS SOURCE BUILDER CLONE URL: git://git.rtems.org/rtems-source-builder.git


mkdir -p ${HOME}/rtems-5
git clone -b 5 git://git.rtems.org/rtems-source-builder.git
cd rtems-source-builder/rtems
../source-builder/sb-set-builder --prefix=$HOME/rtems-5 5/rtems-i386


2) Clone/Bootstrap RTEMS source tree:

Note - at the time of this writing 5.1 is the current "stable" branch and
5.1 represents the latest point release tag on that branch. We are going to
use the "5" branch, which will eventually be released as 5.2. The latest
5 branch has a bux fix for the RFS file system needed by the cFS for this target.
If you use the 5.1 release tag (or tarball) you will most likely not be able
to run the cFS without an error.

OFFICIAL RTEMS CLONE URL: git://git.rtems.org/rtems.git

$ git clone -b 5 git://git.rtems.org/rtems.git
$ export PATH=$HOME/rtems-5/bin:$PATH
$ (cd rtems && ./bootstrap)

3) Build/Install RTEMS pc686 BSP

Note - use same terminal as previous step, or set PATH environment again.
The "prefix" can be whatever location is preferable for installation.

$ mkdir b-pc686
$ cd b-pc686
$ ../rtems/configure --target=i386-rtems5 \
    --enable-rtemsbsp=pc686 \
    --prefix=${HOME}/rtems-5 \
    --enable-networking \
    --enable-cxx \
    --disable-posix \
    --disable-deprecated

$ make
$ make install
$ cd ..

4) RTEMS build module for CMake

This tells CMake how to build basic binaries for RTEMS - it does not know how to do this
"out of the box" on a stock install.

An "RTEMS.cmake" module is now directly included here with the PSP and can be directly 
used by the build system so long as it is included in the CMAKE_MODULE_PATH.  Add a line
like this if not already present (prior to the "project()" function):

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../psp/cmake/Modules" ${CMAKE_MODULE_PATH})


II. Mission setup modifications to use PC-RTEMS PSP

Use a CMake toolchain file to build CFE for RTEMS.  This goes under the mission's "_defs" top-level directory.
This example below may be edited and tuned to the mission-specific needs.

Specifically this file should be called "toolchain-<ARCHNAME>.cmake" where <ARCHNAME> can be anything such as 
"cpu3" or "i686-pc-rtems".

Then in the "targets.cmake" file set the "TGT<N>_PLATFORM" variable to be the same ARCHNAME and the toolchain
file will be picked up and used by the build system.

====== START OF EXAMPLE TOOLCHAIN FILE: CUT HERE ===========
# This example toolchain file describes the cross compiler to use for
# the target architecture indicated in the configuration file.

# In this sample application, the cross toolchain is configured to
# use a compiler for the RTEMS operating system targeting the "pc686" BSP

# Note that to use this, the "RTEMS" platform module may need to be added 
# to the system-wide CMake installation as a default CMake does not yet 
# recognize RTEMS as a system name.  An example of this is distributed with
# the pc-rtems PSP.

# Basic cross system configuration
set(CMAKE_SYSTEM_NAME       RTEMS)
set(CMAKE_SYSTEM_PROCESSOR  i386)
set(CMAKE_SYSTEM_VERSION    5)

# The TOOLS and BSP are allowed to be installed in different locations.
# If the README was followed they will both be installed under $HOME
# By default it is assumed the BSP is installed to the same directory as the tools
SET(RTEMS_TOOLS_PREFIX "$ENV{HOME}/rtems-${CMAKE_SYSTEM_VERSION}" CACHE PATH
    "RTEMS tools install directory")
SET(RTEMS_BSP_PREFIX "${RTEMS_TOOLS_PREFIX}" CACHE PATH
    "RTEMS BSP install directory")

# The BSP that will be used for this build
set(RTEMS_BSP "pc686")

# specify the cross compiler - adjust accord to compiler installation
# This uses the compiler-wrapper toolchain that buildroot produces
SET(SDKHOSTBINDIR               "${RTEMS_TOOLS_PREFIX}/bin")
set(TARGETPREFIX                "${CMAKE_SYSTEM_PROCESSOR}-rtems${CMAKE_SYSTEM_VERSION}-")
set(RTEMS_BSP_C_FLAGS           "-march=i686 -mtune=i686 -fno-common")
set(RTEMS_BSP_CXX_FLAGS         ${RTEMS_BSP_C_FLAGS})


SET(CMAKE_C_COMPILER            "${RTEMS_TOOLS_PREFIX}/bin/${TARGETPREFIX}gcc")
SET(CMAKE_CXX_COMPILER          "${RTEMS_TOOLS_PREFIX}/bin/${TARGETPREFIX}g++")
SET(CMAKE_LINKER                "${RTEMS_TOOLS_PREFIX}/bin/${TARGETPREFIX}ld")
SET(CMAKE_ASM_COMPILER          "${RTEMS_TOOLS_PREFIX}/bin/${TARGETPREFIX}as")
SET(CMAKE_STRIP                 "${RTEMS_TOOLS_PREFIX}/bin/${TARGETPREFIX}strip")
SET(CMAKE_NM                    "${RTEMS_TOOLS_PREFIX}/bin/${TARGETPREFIX}nm")
SET(CMAKE_AR                    "${RTEMS_TOOLS_PREFIX}/bin/${TARGETPREFIX}ar")
SET(CMAKE_OBJDUMP               "${RTEMS_TOOLS_PREFIX}/bin/${TARGETPREFIX}objdump")
SET(CMAKE_OBJCOPY               "${RTEMS_TOOLS_PREFIX}/bin/${TARGETPREFIX}objcopy")

# Exception handling is very iffy.  These two options disable eh_frame creation.
set(CMAKE_C_COMPILE_OPTIONS_PIC -fno-exceptions -fno-asynchronous-unwind-tables)

# Link libraries needed for an RTEMS 5.x executable
#  This was handled by the bsp_specs file in 4.11
set(LINK_LIBRARIES              "-lrtemsdefaultconfig -lrtemsbsp -lrtemscpu")

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM   NEVER)

# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY   ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE   ONLY)

SET(CMAKE_PREFIX_PATH                   /)

# these settings are specific to cFE/OSAL and determines which
# abstraction layers are built when using this toolchain
SET(CFE_SYSTEM_PSPNAME                  pc-rtems)
SET(OSAL_SYSTEM_BSPTYPE                 pc-rtems)
SET(OSAL_SYSTEM_OSTYPE                  rtems)

# This is for RTEMS 5 specific ifdefs needed by the OSAL
ADD_DEFINITIONS(-D_RTEMS_5_)

# Info regarding the RELOCADDR:
#+--------------------------------------------------------------------------+
#| Set the value of RELOCADDR to the address where you want your image to
#| load. If you'll be using GRUB to load the images it will have to be >=
#| 0x100000 (1024K). If you are using NetBoot to load the images it can be
#| >= 0x10000 (64K) AND <= 0x97C00 (607K) OR >= 0x100000 (1024K). The memory
#| top is of course another limit. Make sure there is enough space before the
#| upper memory limits for the image and the memory allocated by it to fit.
#| Make sure the value you choose is aligned to 4 bytes.
#+--------------------------------------------------------------------------+
set(RTEMS_RELOCADDR 0x00100000)

====== END OF EXAMPLE TOOLCHAIN FILE: CUT HERE ===========

2) Get RTEMS GRUB boot image

NOTE: The GRUB image is not needed when using QEMU.  The "-kernel" option to QEMU makes things
much easier and is highly recommended.

RTEMS binaries cannot be directly booted by a PC BIOS...  Grub is one way to boot RTEMS.

Instructions for building GRUB for use with RTEMS@

https://devel.rtems.org/wiki/Building/Grub

If using grub, create a grub configuration file to work with the boot image

Minimal example below.  Replace <TGTNAME> accordingly, and can be otherwise modified as needed.

====== START OF EXAMPLE rtems-grub.cfg FILE: CUT HERE ===========

set default=0
set timeout=1

# Basic menu entry that boots with the console on the emulated VGA screen
menuentry <TGTNAME>-console { multiboot (hd0,0)/core-<TGTNAME>.exe }

# Alternative menu entry to output the RTEMS console to COM1: 
menuentry <TGTNAME>-com1 { multiboot (hd0,0)/core-<TGTNAME>.exe --console=com1 }

====== END OF EXAMPLE rtems-grub.cfg FILE: CUT HERE ===========

NOTE - This should be called "<TGTNAME>_rtems-grub.cfg" for the target_add_hook macro to find it
 
This can also be auto-generated by adding a "FILE(WRITE)" cmake command to the 
"target_add_hook" macro in the toolchain file above.  However by explicitly writing 
the file per cpu this gives extra control / tunability.




III. Building and Running CFE

1) Build mission as normal and run "make install" to copy binaries to /exe (if using cmake makefile wrapper)

2) A minimal QEMU boot sequence for reference (assuming "cpu1")

qemu-system-i386 -m 128 \ 
    -kernel ${INSTALL_DIR}/cpu1/core-cpu1.exe \
    -drive file=fat:rw:${INSTALL_DIR}/cpu1,format=raw \
    -nographic \
    -no-reboot \
    -append "--console=/dev/com1"
    
where ${INSTALL_DIR} represents the filesystem location of the installed binaries from "make install"

Note that the "fat" emulation used above is fairly limited, generally only useful for read-only testing.
To get read-write operation one would have to create real filesystem images and copy files into them, then 
use the images directly.  This is also what would need to be done to deploy on real hardware.

The "-no-reboot" flag causes QEMU to exit if a panic or shutdown event occurs, rather than emulating
an actual processor reset.  This is generally a good thing when debugging, since a bad build can
cause a reset loop.   This flag can be omitted if one wishes to emulate the processor reset.


3) Network-enabled boot sequence.

This is an example QEMU command that includes a simulated network device.  This works with the 
"CI_LAB" / "TO_LAB" apps to allow commands and telemetry from CFE to be exchanged with the host PC.

The "device" and "netdev" options can be tuned to your preferences (see documentation)

qemu-system-i386 -m 128 -nographic -no-reboot \
    -kernel ${INSTALL_DIR}/cpu1/core-cpu1.exe \
    -drive file=fat:rw:${INSTALL_DIR}/cpu1,format=raw \
    -device i82557b,netdev=net0,mac=00:04:9F:00:27:61 \
    -netdev user,id=net0,hostfwd=udp:127.0.0.1:1235-:1235 \
    -append "--console=/dev/com1"
    
One can then use the "cmdutil" and "tlm_decode" applications to interact with the CFE.

4) Automated/scripted Unit-testing configuration using QEMU
 
The Unit Test BSP (utbsp) by default will start an RTEMS shell and allow
an interactive user to query/interact with the system as part of the unit testing.

The BSP also supports a "--batch-mode" option which is intended for 
automated or script-based execution.  It can be invoked through QEMU's 
"-append" option or through the GRUB bootloader if using real hardware.
When using QEMU this allows for  fully scripted testing.  

The basic QEMU command to execute a single unit test is:

qemu-system-i386 -m 128 \
   -kernel ${test-executable}.exe \
   -append '--batch-mode' \
   -nographic -no-reboot \
   -append "--console=/dev/com1" \
       > log-${test-executable}.txt


The entire suite of unit tests can be executed using a for loop:

for i in *test.exe *UT.exe; do \
   qemu-system-i386 -m 128 -kernel $i -append '--batch-mode' -nographic -no-reboot -append "--console=/dev/com1" \
       | tee log-${i%%.exe}.txt;  \
done

