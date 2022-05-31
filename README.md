![Static Analysis](https://github.com/nasa/psp/workflows/Static%20Analysis/badge.svg)
![Format Check](https://github.com/nasa/psp/workflows/Format%20Check/badge.svg)

# Core Flight System : Framework : Platform Support Package

This repository contains NASA's Platform Support Package (PSP), which is a framework component of the Core Flight System.

This is a collection of APIs abstracting platform specific functionality to be located in the `psp` subdirectory of a cFS Mission Tree. The Core Flight System is bundled at <https://github.com/nasa/cFS>, which includes build and execution instructions.

## Version History

### Development Build: v1.6.0-rc4+dev38

- Resolve uninit var static analysis warning
- See <https://github.com/nasa/PSP/pull/346> and <https://github.com/nasa/cFS/pull/492>

### Development Build: v1.6.0-rc4+dev34

- Update codeql workflow for reusable updates
- Add cpu affinity example
- Update RTEMS CMake Platform File
- See <https://github.com/nasa/PSP/pull/343> and <https://github.com/nasa/cFS/pull/471>

### Development Build: v1.6.0-rc4+dev21

- Standardize version.h
- Update Copyright Header
- See <https://github.com/nasa/PSP/pull/330> and <https://github.com/nasa/cFS/445>


### Development Build: v1.6.0-rc4+dev14

- Remove explicit filename doxygen comments
- Apply header guard standard
- See <https://github.com/nasa/PSP/pull/326> and <https://github.com/nasa/cFS/pull/432>


### Development Build: v1.6.0-rc4+dev6

- Sleep before exit when printing
- Check the address in PSP get segment stubs
- Set Build Baseline for cFS-Caelum-rc4: v1.6.0-rc4
- See <https://github.com/nasa/PSP/pull/318> and <https://github.com/nasa/cFS/pull/390>

### Development Build: v1.5.0-rc1+dev124

- Relax strict of check before calling "Init" function of module, only check that module type is not invalid
- Remove override of `add_psp_module` for coverage test
- See <https://github.com/nasa/PSP/pull/307> and <https://github.com/nasa/cFS/pull/351>

### Development Build: v1.5.0-rc1+dev118

- Implement Coding Standards in CodeQL
- rename doc to docs
- See <https://github.com/nasa/PSP/pull/296> and <https://github.com/nasa/cFS/pull/265/>

### Development Build: v1.5.0-rc1+dev112

- Cleans up stale code from the previous methods of generating 1Hz. Adds a new PSP module that instantiates an OSAL abstract timebase for use with cFE services. This single module is used across all psp implementations (mcp750, pc-linux, pc-rtems). Results in 1Hz timing tick on MCP750 will be more accurate. No changes to Linux or RTEMS
- Fixes segfaults when `CFE_PSP_Port` routines are invoked on Linux.
- Converts `cfe_psp_ram.c` and `cfe_psp_port.c` into modular components and removes from the "shared" directory. The existing implementations become the corresponding "direct" module, and are enabled based on the psp module selection. Adds a "notimpl" variant where all the functions return `CFE_PSP_ERR_NOT_IMPLEMENTED`. This is used on Linux
or any other system where direct access is not possible.  Renames the existing `eeprom_stub` module to be `eeprom_notimpl` for consistency and to avoid confusion with the unit test stubs.
- Implements two PSP modules to provide `CFE_PSP_GetTime` and `CFE_PSP_GetTimeBase`, one for POSIX-compliant RTOS using `clock_gettime()` and the other specifically for PowerPC processors on VxWorks that have the `vxTimeBaseGet()` routine. Clarifies and documents the difference and use cases for `CFE_PSP_GetTime` and `CFE_PSP_GetTimeBase`. No impact to behavior.
- Adds a coverage test for the VxWorks PSP timebase module and provides an example of how this can be implemented for other modules.
- See <https://github.com/nasa/PSP/pull/289> and <https://github.com/nasa/cFS/pull/238>

### Development Build: v1.5.0-rc1+dev101

- Removes unnecessary global config structure `Target_PspConfigData` and associated elements in favor of the new version API.
- The mem pool stats TLM command now works on 64-bit Linux and sends out the expected telemetry packet.
Converts `CFE_PSP_MemoryTable` to internal object (instead of external) that should only be accessed via the PSP API. Replace `uint32`s with `size_t`. Use full range (SIZE_MAX) in the Linux/RTEMS implementation.
- See <https://github.com/nasa/PSP/pull/288> and <https://github.com/nasa/cFS/pull/233>

### Development Build: v1.5.0-rc1+dev95

- Includes `cfe_psp_version.c` in the cmake source list, which was mistakenly omitted previously.
- Applied the patch and confirmed that CS Cmake unit tests build. Unit tests relying on `CFE_PSP_GetKernelTextSegmentInfo` will build.
- See <https://github.com/nasa/PSP/pull/279>

### Development Build: v1.5.0-rc1+dev90

- Addresses the issue of incompatible/non-portable code blobs in the "shared" directory. It uses the same modular init pattern as is used elsewhere in cFE: CMake generates a list of "base" modules correlating with the selected PSP (i.e. pc-linux, mcp750-vxworks, etc) and these modules are then initialized (in order) before the rest of PSP runs. The "direct write" EEPROM is not used unconditionally. Instead the proper eeprom implementation module is selected based on which PSP is selected. MCP750 uses direct write, pc-linux uses an mmap file, and pc-rtems uses a stub (not implemented).
- Replaces " used on non-system header #includes with <>
- Adds a contributing guide that links to the main cFS contributing guide.
- See <https://github.com/nasa/PSP/pull/273>


### Development Build: v1.5.0-rc1+dev82

- HOTFIX 20210312, updates to work with older CMake
- See <https://github.com/nasa/PSP/pull/268>

### Development Build: v1.5.0-rc1+dev76

- Fix #246, remove unused code.
- Fix #254, use CMake to publish interface details
- Fix #256, add PSP version API
- Fix #258, Add Testing Tools to the Security Policy
- See <https://github.com/nasa/PSP/pull/260>

### Development Build: 1.5.0-rc1+dev68

- Updates continuous integration workflow by adding static analysis with timeout and code format check. Adds status badges to ReadMe and removes old TravisCI artifacts.
- Adds CodeQL analysis to continuous integration
- Apply standard formatting to psp codebase. Only changes whitespace.
- Adds missing "+dev" to development version output
- See <https://github.com/nasa/PSP/pull/250>

### Development Build: 1.5.0-rc1+dev58

- Add `Security.md` with instructions on reporting vulnerabilities.
- Rename `UT_ClearForceFail` as `UT_ClearDefaultValue` to reflect <https://github.com/nasa/osal/issues/724>
- Remove unused elements in `CFE_PSP_ModuleType_t` enum to avoids irregular enum warning
- See <https://github.com/nasa/PSP/pull/243>

### Development Build: 1.5.0-rc1+dev50

-  Instead of accessing `OS_time_t` member values directly, use the OSAL-provided conversion and access methods. This provides independence and abstraction from the specific `OS_time_t` definition and allows OSAL to transition to a 64 bit value.
- See <https://github.com/nasa/psp/pull/240>

### Development Build: 1.5.0-rc1+dev46

- Add cppcheck GitHub Actions workflow file
- See <https://github.com/nasa/PSP/pull/234>


### Development Build: 1.5.0-rc1+dev42

- Updates the Readme for RTEMS and adds `README_RTEMS_5.txt`. The changes include removing references to the CEXP module loader, and describing the development environment setup for RTEMS 5.  
- Remove obsolete OS_TaskRegister comment.  
- See <https://github.com/nasa/PSP/pull/226>


### Development Build: 1.5.0-rc1+dev36

- Rename `UT_SetForceFail` to `UT_SetDefaultReturnValue` since some functions that retain more than 1 value are not necessarily failing.
- Use of the size_t type instead of uint32 in unit-tests to avoid a compiler type mismatch error on some platforms.
- See <https://github.com/nasa/PSP/pull/221>

### Development Build: 1.5.0-rc1+dev30

- - Use event callback mechanism to invoke pthread_setname_np() such that the OS kernel is informed of the OSAL task name. `/proc` filesystem on Linux now has actual task name, instead of all being core-cpu1. The `pthread_setname_np` API requires `_GNU_SOURCE` to be defined when compiling - this can be local to PSP.
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
