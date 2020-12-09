Travis-CI: [![Build Status](https://travis-ci.com/nasa/PSP.svg)](https://travis-ci.com/nasa/PSP)

# Core Flight System : Framework : Platform Support Package

This repository contains NASA's Platform Support Package (PSP), which is a framework component of the Core Flight System.

This is a collection of APIs abstracting platform specific functionality to be located in the `psp` subdirectory of a cFS Mission Tree. The Core Flight System is bundled at <https://github.com/nasa/cFS>, which includes build and execution instructions.

## Version History

### Development Build: 1.5.0-rc1+dev42

- Updates the Readme for RTEMS and adds `README_RTEMS_5.txt`. The changes include removing references to the CEXP module loader, and describing the development environment setup for RTEMS 5.  
- Remove obsolete OS_TaskRegister comment.  
- See <https://github.com/nasa/PSP/pull/226>


### Development Build: 1.5.0-rc1+dev36

- Rename `UT_SetForceFail` to `UT_SetDefaultReturnValue` since some functions that retain more than 1 value are not necessarily failing.
- Use of the size_t type instead of uint32 in unit-tests to avoid a compiler type mismatch error on some platforms.
- See <https://github.com/nasa/PSP/pull/221>

### Development Build: 1.5.0-rc1+dev30

- PR #212 - Use event callback mechanism to invoke pthread_setname_np() such that the OS kernel is informed of the OSAL task name. `/proc` filesystem on Linux now has actual task name, instead of all being core-cpu1. The `pthread_setname_np` API requires `_GNU_SOURCE` to be defined when compiling - this can be local to PSP.
- Set REVISION to "99" to indicate development version
- See <https://github.com/nasa/PSP/pull/213>

### Development Build: 1.5.0-rc1+dev24

- Improves the module ID lookup when getting the CFE core text segment info. VxWorks PSP should use the real module name, not assume cfe-core.o when getting text segment info
- See <https://github.com/nasa/PSP/pull/209>

### Development Build: 1.5.0-rc1+dev19

- Use the osal_id_t typedef whenever dealing with an OSAL ID value.
- Resolves build error regarding redefinition of PPC macros in the coverage test, when building on the actual ppc/vxworks target.
- See <https://github.com/nasa/PSP/pull/206>

### Development Build: 1.5.0-rc1+dev14

- Sets the stub config data spacecraft id to historical value 0x42, was 42.
- Installs unit test to target directories.
- See <https://github.com/nasa/PSP/pull/196>

### Development Build: 1.5.0-rc1+dev6

- Adds CFE_PSP_GetProcessorName
- Removes classic make artifacts
- See <https://github.com/nasa/PSP/pull/190>

### Development Build: 1.4.0+dev76

- Provide a new framework and perform PSP coverage tests. New coverage test executable is built and several files within PSP are targeted.
- See <https://github.com/nasa/PSP/pull/184>

### Development Build: 1.4.0+dev71

- Restructure code to make more amicable for rebuilding in a unit test environment. No major changes, primarily just shifting code between locations/headers to support unit testing.
-  Adds a char element `Version` to `CFE_PSP_VersionInfo_t` containing the version number expressed as a string. Defines new macros for the Build Number and the Build Baseline.
- See <https://github.com/nasa/PSP/pull/176>

### Development Build: 1.4.14

- Changes the PSP reference to be compatible with the change in nasa/osal#449 making the BSP modules more generic and changes the name.
- See <https://github.com/nasa/PSP/pull/175>

### Development Build: 1.4.13

- Changes the PSP reference to be compatible with the change in nasa/osal#449 making the BSP modules more generic and changes the name.
- See <https://github.com/nasa/PSP/pull/167>

### Development Build: 1.4.12

- Replace 'OS_VolumeTable' with OS_FileSysAddFixedMap() in all PSPs.
- See <https://github.com/nasa/PSP/pull/166>

### Development Build: 1.4.11

- Removes non-termination string warnings when building with GCC9.
- Exception handling is now implemented on POSIX. There is no longer a separate handler for SIGINT - it is now treated as an exception and goes through the normal process which ends up "restarting" CFE. On pc-linux causes the process to exit normally. There is now a mechanism to capture the CTRL+C exception code and use it during normal test cycles.
- See <https://github.com/nasa/PSP/pull/160>

### Development Build: 1.4.10

- Implements full-precision microsecond conversion
- See <https://github.com/nasa/PSP/pull/155>

### Development Build: 1.4.9

- RTEMS builds successfully without errors
- Build script uses a proper CMakeLists.txt instead of the aux_source directory
- Minor updates (see <https://github.com/nasa/PSP/pull/153>)

### Development Build: 1.4.8

- Minor updates (see <https://github.com/nasa/PSP/pull/151>)

### Development Build: 1.4.7

- Fixed some build warnings for MCP750
- Minor updates (see <https://github.com/nasa/PSP/pull/142>)

### Development Build: 1.4.6

- Minor updates (see <https://github.com/nasa/PSP/pull/141>)

### Development Build: 1.4.5

- Simplifies array handling in VxWorks
- Minor updates (see <https://github.com/nasa/PSP/pull/138>)

### Development Build: 1.4.4

- Minor updates (see <https://github.com/nasa/PSP/pull/132>)

### Development Build: 1.4.3

- Minor updates (see <https://github.com/nasa/PSP/pull/130>)

### Development Build: 1.4.2

- Minor updates (see <https://github.com/nasa/PSP/pull/127>)

### Development Build: 1.4.1

- Minor updates (see <https://github.com/nasa/PSP/pull/115>)

### **_1.4.0 OFFICIAL RELEASE - Aquila_**

- This is a point release from an internal repository
- Changes are detailed in [cFS repo](https://github.com/nasa/cFS) release documentation
- Released as part of cFE 6.7.0, Apache 2.0

### **_1.3.0a OFFICIAL RELEASE_**

- This is a point release from an internal repository
- See [version description document](https://github.com/nasa/PSP/blob/v1.3.0a/doc/PSP%201.3.0.0%20Version%20Description%20Document.pdf)
- Released as part of cFE 6.6.0a, Apache 2.0

The open source release does not include all PSPs that have been developed. Only the three PSPs included are managed by the community CCB. PSPs developed by other organizations can be requested through the mechanisms listed below. Note the framework PSPs delivered may change in the future as platforms become obsolete.

## Known issues

See all open issues and closed to milestones later than this version.

## Getting Help

For best results, submit issues:questions or issues:help wanted requests at <https://github.com/nasa/cFS>.

Official cFS page: <http://cfs.gsfc.nasa.gov>
