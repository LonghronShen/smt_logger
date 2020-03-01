project(smt_logger CXX)

file(GLOB_RECURSE src
  ${CMAKE_CURRENT_LIST_DIR}/*.h
  ${CMAKE_CURRENT_LIST_DIR}/*.hpp

  ${CMAKE_CURRENT_LIST_DIR}/*.c
  ${CMAKE_CURRENT_LIST_DIR}/*.cc
  ${CMAKE_CURRENT_LIST_DIR}/*.cpp
)

file(GLOB_RECURSE SMT_LOGGER_HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/include/*.h
  ${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# Get version from core.h
file(READ "${CMAKE_CURRENT_LIST_DIR}/include/smt_logger.h" smt_logger_h)
if (NOT smt_logger_h MATCHES "SMT_LOGGER_VERSION ([0-9]+)([0-9][0-9])([0-9][0-9])")
  message(FATAL_ERROR "Cannot get SMT_LOGGER_VERSION from smt_logger.h.")
endif ()

# Use math to skip leading zeros if any.
math(EXPR CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_MATCH_1})
math(EXPR CPACK_PACKAGE_VERSION_MINOR ${CMAKE_MATCH_2})
math(EXPR CPACK_PACKAGE_VERSION_PATCH ${CMAKE_MATCH_3})

join(SMT_LOGGER_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
message(STATUS "Version: ${SMT_LOGGER_VERSION}")

if(UNIX)
  add_library(smt_logger SHARED ${src})
elseif(WIN32)
  add_library(smt_logger STATIC ${src})
elseif(APPLE)
  add_library(smt_logger SHARED ${src})
endif()

target_include_directories(smt_logger
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>)

target_link_libraries(smt_logger
  PRIVATE ${CMAKE_THREAD_LIBS_INIT}
  PUBLIC fmt::fmt
  PUBLIC spdlog::spdlog)


# install script
if (SMT_LOGGER_INSTALL)
  include(GNUInstallDirs)
  include(CMakePackageConfigHelpers)

  set(SMT_LOGGER_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/smy_logger CACHE STRING "Installation directory for cmake files, relative to ${CMAKE_INSTALL_PREFIX}.")
  set(version_config ${PROJECT_BINARY_DIR}/smt-logger-config-version.cmake)
  set(project_config ${PROJECT_BINARY_DIR}/smt-logger-config.cmake)
  set(pkgconfig ${PROJECT_BINARY_DIR}/smt-logger.pc)
  set(targets_export_name smt-logger-targets)

  set (INSTALL_TARGETS smt-logge)
  set(SMT_LOGGER_LIB_DIR ${CMAKE_INSTALL_LIBDIR} CACHE STRING "Installation directory for libraries, relative to ${CMAKE_INSTALL_PREFIX}.")
  set(SMT_LOGGER_INC_DIR ${CMAKE_INSTALL_INCLUDEDIR}/smt-logger CACHE STRING "Installation directory for include files, relative to ${CMAKE_INSTALL_PREFIX}.")
  set(SMT_LOGGER_PKGCONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/pkgconfig CACHE PATH "Installation directory for pkgconfig (.pc) files, relative to ${CMAKE_INSTALL_PREFIX}.")

  # Generate the version, config and target files into the build directory.
  write_basic_package_version_file(
    ${version_config}
    VERSION ${SMT_LOGGER_VERSION}
    COMPATIBILITY AnyNewerVersion)
  configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/fmt.pc.in"
    "${pkgconfig}"
    @ONLY)
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/smt-logger-config.cmake.in
    ${project_config}
    INSTALL_DESTINATION ${SMT_LOGGER_CMAKE_DIR})

  # Use a namespace because CMake provides better diagnostics for namespaced
  # imported targets.
  export(TARGETS ${INSTALL_TARGETS} NAMESPACE Leica::
         FILE ${PROJECT_BINARY_DIR}/${targets_export_name}.cmake)

  # Install version, config and target files.
  install(
    FILES ${project_config} ${version_config}
    DESTINATION ${SMT_LOGGER_CMAKE_DIR})
  install(EXPORT ${targets_export_name} DESTINATION ${SMT_LOGGER_CMAKE_DIR}
          NAMESPACE fmt::)

  # Install the library and headers.
  install(TARGETS ${INSTALL_TARGETS} EXPORT ${targets_export_name}
          LIBRARY DESTINATION ${SMT_LOGGER_LIB_DIR}
          ARCHIVE DESTINATION ${SMT_LOGGER_LIB_DIR}
          RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

  install(FILES $<TARGET_PDB_FILE:${INSTALL_TARGETS}>
          DESTINATION ${SMT_LOGGER_LIB_DIR} OPTIONAL)
  install(FILES ${SMT_LOGGER_HEADERS} DESTINATION ${SMT_LOGGER_INC_DIR})
  install(FILES "${pkgconfig}" DESTINATION "${SMT_LOGGER_PKGCONFIG_DIR}")
endif()