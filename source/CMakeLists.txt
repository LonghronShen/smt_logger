project(${project_name}-lib VERSION 1.0.0 LANGUAGES C CXX)

aux_source_directory("${CMAKE_CURRENT_LIST_DIR}/lib" DIR_SRCS)

file(GLOB_RECURSE public_headers
    ${CMAKE_CURRENT_LIST_DIR}/include/*.h
    ${CMAKE_CURRENT_LIST_DIR}/include/*.hpp
)

add_library(${project_name}-lib STATIC ${DIR_SRCS})

target_compile_features(${project_name}-lib
    PUBLIC cxx_std_17)

set_target_properties(${project_name}-lib PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON)

target_link_libraries(${project_name}-lib
    PUBLIC ${CMAKE_THREAD_LIBS_INIT}
    PUBLIC fmt::fmt
    PUBLIC spdlog::spdlog
)

target_include_directories(${project_name}-lib
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include"
)

# ------------------------------- install script -------------------------------
# Prepare exposed headers
set_target_properties(${project_name}-lib PROPERTIES PUBLIC_HEADER "${public_headers}")

set(BIN_INSTALL_DIR "bin/" CACHE STRING "BIN_INSTALL_DIR" FORCE)
set(INCLUDE_INSTALL_DIR "include/" CACHE STRING "INCLUDE_INSTALL_DIR" FORCE)
set(LIB_INSTALL_DIR "lib/" CACHE STRING "LIB_INSTALL_DIR" FORCE)
set(SYSCONFIG_INSTALL_DIR "etc/${project_name}/" CACHE STRING "SYSCONFIG_INSTALL_DIR" FORCE)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/cmake/smt-loggerConfig.cmake.in"
    ${CMAKE_CURRENT_BINARY_DIR}/smt-loggerConfig.cmake
    INSTALL_DESTINATION "${LIB_INSTALL_DIR}/${project_name}/cmake"
    PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/smt-loggerConfigVersion.cmake
	VERSION "${PACKAGE_VERSION}"
	COMPATIBILITY SameMajorVersion)

install(TARGETS ${project_name}-lib
    EXPORT ${project_name}-lib DESTINATION ${LIB_INSTALL_DIR}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
    PUBLIC_HEADER DESTINATION include/${project_name}
)

install(
	EXPORT ${project_name}-lib DESTINATION ${LIB_INSTALL_DIR}
	# EXPORT fmt::fmt DESTINATION ${LIB_INSTALL_DIR} FILE fmt.cmake
	# EXPORT spdlog::spdlog DESTINATION ${LIB_INSTALL_DIR} FILE spdlog.cmake
)

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/smt-loggerConfig.cmake
		${CMAKE_CURRENT_BINARY_DIR}/smt-loggerConfigVersion.cmake
	DESTINATION ${LIB_INSTALL_DIR}/${project_name}/cmake
)
