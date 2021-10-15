cmake_minimum_required(VERSION 3.0.0)

# use local repository if defined
if (DEFINED ENV{LOCAL_REPOSITORY})
  set(CMAKE_PREFIX_PATH $ENV{LOCAL_REPOSITORY})
endif()

# use toolchain if possible
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(smt-logger)
enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(source)
add_subdirectory(example)
# add_subdirectory(tests)

# for test
# SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
