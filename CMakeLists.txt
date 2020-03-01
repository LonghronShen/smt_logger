cmake_minimum_required(VERSION 3.1.0)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif()

# Determine if fmt is built as a subproject (using add_subdirectory)
# or if it is the master project.
set(MASTER_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MASTER_PROJECT ON)
  message(STATUS "CMake version: ${CMAKE_VERSION}")
endif ()

# Set the default CMAKE_BUILD_TYPE to Release.
# This should be done before the project command since the latter can set
# CMAKE_BUILD_TYPE itself (it does so for nmake).
if (MASTER_PROJECT AND NOT CMAKE_BUILD_TYPE)
  join(doc "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or "
           "CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING ${doc})
endif ()

option(SMT_LOGGER_INSTALL "Generate the install target." ${MASTER_PROJECT})

project(smt-logger C CXX)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17 CACHE STRING "Set to 11, 14 or 17 to enable C++11, C++14 or C++17 builds, respectively." FORCE)
  set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)
endif()

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11 CACHE STRING "Set to 99 or 11 to enable C99 or C11 builds, respectively." FORCE)
  set_property(GLOBAL PROPERTY C_STANDARD_REQUIRED ON)
endif()

set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if (MASTER_PROJECT AND CMAKE_GENERATOR MATCHES "Visual Studio")
  # If Microsoft SDK is installed create script run-msbuild.bat that
  # calls SetEnv.cmd to set up build environment and runs msbuild.
  # It is useful when building Visual Studio projects with the SDK
  # toolchain rather than Visual Studio.
  include(FindSetEnv)
  if (WINSDK_SETENV)
    set(MSBUILD_SETUP "call \"${WINSDK_SETENV}\"")
  endif ()
  # Set FrameworkPathOverride to get rid of MSB3644 warnings.
  set(netfxpath "C:\\Program Files\\Reference Assemblies\\Microsoft\\Framework\\.NETFramework\\v4.0")
  file(WRITE run-msbuild.bat "
    ${MSBUILD_SETUP}
    ${CMAKE_MAKE_PROGRAM} -p:FrameworkPathOverride=\"${netfxpath}\" %*")
endif ()

# change output dirs
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
  add_definitions(-DLOG_DEBUG)
endif ()

find_package(Threads REQUIRED)

find_package(spdlog CONFIG)
if(NOT spdlog_FOUND)
    find_package(fmt CONFIG)
    if(NOT fmt_FOUND)
        add_subdirectory(external/fmt)
        set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "Use external fmt library instead of bundled" FORCE)
    endif()
    add_subdirectory(external/spdlog)
endif()

add_subdirectory(src)
add_subdirectory(test)
