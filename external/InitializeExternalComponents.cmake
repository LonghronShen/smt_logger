find_package(Threads REQUIRED)

if(UNIX)
  find_package(DL REQUIRED)
endif()

include(FetchContent)

# fmt
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG ef7369ce900346f403472231b60662936b24e731)

FetchContent_GetProperties(fmt)
if(NOT fmt_POPULATED)
  FetchContent_Populate(fmt)
  add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# spdlog
set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "Use external fmt library instead of bundled" FORCE)
FetchContent_Declare(spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG 79259fdb3f57283f65185a8e41840968dae4043c)

FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
  FetchContent_Populate(spdlog)
  add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# gtest
FetchContent_Declare(gtest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG df6b75949b1efab7606ba60c0f0a0125ac95c5af)

FetchContent_GetProperties(gtest)
if(NOT gtest_POPULATED)
  FetchContent_Populate(gtest)
  add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()