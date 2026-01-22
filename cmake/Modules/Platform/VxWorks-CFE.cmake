# -----------------------------------------------------------------
#  CFE-specific CMake Module for VxWorks
#
# The cmake distribution by default may contain a module for VxWorks,
# but different link rules are needed in order to build loadable CFE apps.
#
# This supports VxWorks Downloadable Kernel Module (DKM) and
#  VxWorks Real Time Process (RTP) builds.
#
# For RTP builds, use set(VXWORKS_RTP TRUE), otherwise
# this file will default to the DKM rules
# -----------------------------------------------------------------
set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

if(VXWORKS_RTP)
   # RTP Specific rules
   set(CMAKE_EXECUTABLE_SUFFIX ".vxe")
   set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
   set(CMAKE_SHARED_MODULE_SUFFIX ".so")

   set(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "-shared")
   set(CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG "-Wl,-rpath,")
   set(CMAKE_SHARED_LIBRARY_RUNTIME_C_FLAG_SEP ":")
   set(CMAKE_SHARED_LIBRARY_RPATH_LINK_C_FLAG "-Wl,-rpath-link,")
   set(CMAKE_SHARED_LIBRARY_SONAME_C_FLAG "-Wl,-soname,")

   set(CMAKE_SHARED_LIBRARY_C_FLAGS "-fPIC")
   set(CMAKE_SHARED_LIBRARY_CXX_FLAGS "")
   set(CMAKE_SHARED_MODULE_C_FLAGS "-fPIC")
   set(CMAKE_SHARED_MODULE_CXX_FLAGS "")

   set(CMAKE_SHARED_OBJECT_LINKER_FLAGS -shared)
   set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <LINK_FLAGS> -o <TARGET> -rdynamic <OBJECTS> <LINK_LIBRARIES>")
else()
   # DKM Specific rules
   set(CMAKE_EXECUTABLE_SUFFIX ".exe")
   set(CMAKE_SHARED_LIBRARY_SUFFIX ".o")
   set(CMAKE_SHARED_MODULE_SUFFIX ".o")

   # Setting all these to empty string defeats the default behavior
   # of adding an -fPIC option to shared library/module code.
   set(CMAKE_DL_LIBS "")
   set(CMAKE_C_COMPILE_OPTIONS_PIC "")
   set(CMAKE_CXX_COMPILE_OPTIONS_PIC "")

   set(CMAKE_SHARED_LIBRARY_C_FLAGS "")
   set(CMAKE_SHARED_LIBRARY_CXX_FLAGS "")
   set(CMAKE_SHARED_MODULE_C_FLAGS "")
   set(CMAKE_SHARED_MODULE_CXX_FLAGS "")

   set(CMAKE_SHARED_OBJECT_LINKER_FLAGS -r)
   set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> <LINK_FLAGS> -o <TARGET> ${CMAKE_SHARED_OBJECT_LINKER_FLAGS} <OBJECTS> <LINK_LIBRARIES>")
endif()

# This creates a simple relocatable object file, not a shared library
set(CMAKE_C_CREATE_SHARED_MODULE "<CMAKE_LINKER> <LINK_FLAGS> -o <TARGET> ${CMAKE_SHARED_OBJECT_LINKER_FLAGS} <OBJECTS> <LINK_LIBRARIES>")
set(CMAKE_CXX_CREATE_SHARED_MODULE ${CMAKE_C_CREATE_SHARED_MODULE})
set(CMAKE_C_CREATE_SHARED_LIBRARY ${CMAKE_C_CREATE_SHARED_MODULE})
set(CMAKE_CXX_CREATE_SHARED_LIBRARY ${CMAKE_C_CREATE_SHARED_MODULE})

set(VXWORKS_TARGET_PATH "${WIND_HOME}/vxworks-${CMAKE_SYSTEM_VERSION}/target")

set(CMAKE_FIND_ROOT_PATH "${VXWORKS_TARGET_PATH}")
set(CMAKE_SYSTEM_PREFIX_PATH "${VXWORKS_TARGET_PATH}")
set(CMAKE_SYSTEM_INCLUDE_PATH "${VXWORKS_TARGET_PATH}/h")
    
set(CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES ${CMAKE_SYSTEM_INCLUDE_PATH})
set(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES ${CMAKE_SYSTEM_INCLUDE_PATH})
