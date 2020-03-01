project(smt-logger-lib CXX)

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

set(SMT_LOGGER_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
message(STATUS "SMT Logger Version: ${SMT_LOGGER_VERSION}")

if(UNIX)
  add_library(smt-logger-lib SHARED ${src})
elseif(WIN32)
  add_library(smt-logger-lib STATIC ${src})
elseif(APPLE)
  add_library(smt-logger-lib SHARED ${src})
endif()

add_library(Leica::smt-logger ALIAS smt-logger-lib)

set(SMT_LOGGER_DEBUG_POSTFIX d)

set_target_properties(smt-logger-lib PROPERTIES
  VERSION ${SMT_LOGGER_VERSION} SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}
  DEBUG_POSTFIX ${SMT_LOGGER_DEBUG_POSTFIX})

target_include_directories(smt-logger-lib
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_link_libraries(smt-logger-lib
  PRIVATE ${CMAKE_THREAD_LIBS_INIT}
  PRIVATE fmt::fmt
  PRIVATE spdlog::spdlog)


# install script
if(SMT_LOGGER_INSTALL)
  include(GNUInstallDirs)
  include(CMakePackageConfigHelpers)

  set(SMT_LOGGER_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/smy_logger CACHE STRING "Installation directory for cmake files, relative to ${CMAKE_INSTALL_PREFIX}.")
  set(version_config ${PROJECT_BINARY_DIR}/smt-logger-config-version.cmake)
  set(project_config ${PROJECT_BINARY_DIR}/smt-logger-config.cmake)
  set(pkgconfig ${PROJECT_BINARY_DIR}/smt-logger.pc)
  set(targets_export_name smt-logger-targets)

  set(INSTALL_TARGETS smt-logger-lib fmt spdlog)
  set(SMT_LOGGER_LIB_DIR ${CMAKE_INSTALL_LIBDIR} CACHE STRING "Installation directory for libraries, relative to ${CMAKE_INSTALL_PREFIX}.")
  set(SMT_LOGGER_INC_DIR ${CMAKE_INSTALL_INCLUDEDIR}/smt-logger CACHE STRING "Installation directory for include files, relative to ${CMAKE_INSTALL_PREFIX}.")
  set(SMT_LOGGER_PKGCONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/pkgconfig CACHE PATH "Installation directory for pkgconfig (.pc) files, relative to ${CMAKE_INSTALL_PREFIX}.")

  # Generate the version, config and target files into the build directory.
  write_basic_package_version_file(
    ${version_config}
    VERSION ${SMT_LOGGER_VERSION}
    COMPATIBILITY AnyNewerVersion)
  configure_file(
    "${PROJECT_SOURCE_DIR}/cmake/smt-logger.pc.in"
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
          NAMESPACE Leica::)

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