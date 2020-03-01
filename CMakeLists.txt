cmake_minimum_required(VERSION 3.0.0)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif()

project(smt-logger)

# change output dirs
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_DEBUG_POSTFIX d)

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
