# Generic VxWorks 7 RTP Platform Support Package

# Assumptions:

* The vxworks-rtp OSAL and generic-vxworks-rtp OSAL BSP are used.
* The cFE repository has the necessary CMake toolchain files for VxWorks RTP targets.
* A Compatible VxWorks 7 SDK is available. This was tested on VxWorks SR0650 for the Raspberry Pi 4, the VxWorks Public SDK For the Raspberry Pi 4, and the VxWorks Public SDK for x86_64 QEMU.

## How to build cFS for VxWorks 7 RTP Raspberry Pi 4 target (Public SDK)

This example will focus on the VxWorks Public SDK for the Raspberry Pi 4. This SDK is available to download without a licence and can be used for non-commercial purposes.

### Download and Prepare the VxWorks SDK

* Download the public SDK at this URL: https://forums.windriver.com/t/vxworks-software-development-kit-sdk/43 this example is **VxWorks SDK for Raspberry Pi 4 version 1.6 24.03**
* Unpack the SDK. It is assumed that the directory will be **wrsdk-vxworks7-raspberrypi4b**
* In the directory **wrsdk-vxworks7-raspberrypi4b** edit the file **sdkenv.sh** and comment out the line that defines the CC macro:
```
# export CC=wr-cc
export CXX=wr-c++
export CPP=wr-cpp
```

This is necessary because the current toolchain file for this build depends on the environment script, and the CC definition will cause the cFS elf2cfetbl utility to not compile. An upcoming version of the toolchain file will remove the need to run the SDK setup script.

> [!NOTE]
> Do not run the sdk setup script until the cFS repository is cloned and ready to build.

### Copy the SDK runtime files to a Raspberry Pi SD card
As part of the setup process, the SD card must be prepared with:
* u-boot bootloader
* device tree file(s)
* VxWorks kernel
* VxWorks shared libraries and directories needed

The setup is covered in the SDK README.md file. It is a good idea to verify that the Pi can boot and run VxWorks before moving on to build the cFS.

### Configure and Build the cFS for the Raspberry Pi 4

These instructions cover running the cFS Bundle that has integrated support for VxWorks 7 RTPs.

* Clone the correct branch of the cFS that supports VxWorks 7 RTPs
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
* In the sample_defs directory, edit **targets.cmake** and change the **cpu1_SYSTEM** macro to **aarch-vx7rtp**. Note that this should match the name of the toolchain file you are using. In this case the toolchain file is **toolchain-aarch64-vx7rtp.cmake**.
```
SET(cpu1_PROCESSORID 1)
SET(cpu1_APPLIST ci_lab to_lab sch_lab)
SET(cpu1_FILELIST cfe_es_startup.scr)
SET(cpu1_SYSTEM aarch64-vx7rtp)
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
Now the cFS should be ready to build for the Raspberry Pi 4 VxWorks 7 RTP.

### Build the cFS for Raspberry Pi 4 VxWorks 7 RTP 

> [!NOTE]
> It is assumed that the cfs is cloned to ~/cfs, and the Rasberry Pi 4 SDK is in ~/wrsdk-vxworks7-raspberrypi4b
* Switch back to the directory where the VxWorks 7 SDK is setup. In that directory, run the **sdkenv.sh** script with the following command:
```
cd ~/wrsdk-vxworks7-raspberrypi4b
source sdkenv.sh
```
* Switch back to the cFS directory that has been setup and run the make steps:
```
cd ~/cfs 
make prep
make
make install
```

If the build completes successfully, the cFS binaries, startup script, and tables will be in:
```
build/exe/cpu1
```

### Copy the cFS runtime files to the SD card for the Raspberry Pi 4

* Copy the **cfs/build/exe/cpu1** directory to the Pi 4 SD card root directory. SD card should have **cpu1** at the top level.

### Boot the Pi 4 and run the cFS RTP image

* Insert the SD card with u-boot, the VxWorks kernel and **cpu1** directory into the Pi (The SDK card and these files need to be set up from the Public SDK instructions)
* Open a UART/minicom program to see the UART console
* Power on the Pi
* When the VxWorks shell prompt comes up, type the following:

```
> cmd
# cd /sd0a/cpu1
# core-cpu1.vxe &
```
> [!NOTE]
> You could also configure an FTP server and load the files remotely.

You should see the cFS RTP load and start the services and apps.

You can use commands such as "ps" to list the running RTPs, etc. For more info type:
```
# help rtp
```

### Command the cFS on the Raspberry Pi 4

The CI_LAB and TO_LAB cFS apps use the network to communicate with the ground system via UDP packets. This was tested on a Pi4 connected via ethernet to a local LAN with a DHCP server. Once the Pi 4 boots, it will obtain an IP address and report the address on the UART contols. This can sometimes take a few minutes.

This readme will be expanded with ore information about configuring the Pi4 for a static IP address.
 
### Command line arguments

The cFS uses a number of command line arguments to start and restart the cFS. To see a full list, type:
```
# core-cpu1.vxe -h 
```
The most relevant options are:
* -R PO and -R PR - this is the reset type. The default reset type is PO or Power On. This reset will clear/create the shared memory segments that are used for cFS reserved memory. The PR option is for a Processor Reset. This is used to restart the cFS after it has exited and it will try to re-connect to the shared memory segments that have been created to store the cFS reserved memory.
* -F cfs1 - The -F option is for the "cfs ID". This is currently used as a prefix for the shared memory sement names that the cFS uses for reserved memory. This unique prefix allows multiple cFS RTPs to run on the same OS instance. If you start the cFS with a specific cfs ID, be sure to use it when restarting the cFS. 
As an example, the cFS could be started twice with the following commands:
```
# core-cpu1.vxe -F cfs1 &
# core-cpu1.vxe -F cfs2 &
```
Note that application resources will have to be changed such as the socket that CI_LAB listens to and the socket that TO_LAB sends telemetry packets to.

### Stopping the cFS

If you wish to stop the cFS RTP without powering off the board, you can do the following in the VxWorks Shell:
* Type **ps** then note the ID of the RTP (can copy it into the clipboard):
```
# ps
```
* Type **rtp delete <id>** where the id is the ID that was copied from the previous step:
```
# rtp delete <id>
```
If the network is connected a CFE_ES_RESTART command can also be sent. 


### Work to do / Limitations

This PSP is a starting point for a VxWorks 7 RTP port. It will be expanded over time, but it is also intended to be portable. It is expected that a project will need to customize a PSP for the target hardware and mission requirements.

Some potential future enhancements:
* Improve the Cmake toolchain files to not depend on the VxWorks environment setup script.
* Determine how to manage the warnings in the **arch_build_custom.cmake** file. Some of the warnings can be resolved by updates to the cFS code.
* Determine if we need to replace the "parg" command line parser code. The VxWorks SDK does not provide a command line parser, but later SDKs include the open source "parg" command line parser. It was decided to include the library directly to be compatible with all versions of the SDK. We may want to write a cFS specific library and remove this third party code. It may also be desirable to promote the argument processing code to the shared directory for all PSPs.
* Design and provide kernel mode support code to launch and monitor cFS RTPs.
* Finalize the design for reserved memory. This is likely to be target specific since it relies on how the memory is managed on each target. A portable solution may be to implement the cFE reserved memory as mmapped files on a non-volatile device.
* Determine if we want to include the shared libraries on the target or link them to the cFS builds.
* Add the instructions for a build that uses a VxWorks Source Build (VSB) and VxWorks Image Project (VIP) rather than an SDK.
