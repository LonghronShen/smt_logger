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

install(TARGETS ${project_name}-lib
    EXPORT spdlog::spdlog
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/${project_name}
)

# install(TARGETS ${project_name}-lib
#         EXPORT ${project_name}-libTargets
#         LIBRARY DESTINATION lib
#         ARCHIVE DESTINATION lib
#         RUNTIME DESTINATION bin
#         PUBLIC_HEADER DESTINATION include)

# # Generate library version info which will generate xxxConfigVersion.cmake,
# # the ${PACKAGE_VERSION} is the version defined in project()
# include(CMakePackageConfigHelpers)

# write_basic_package_version_file(
#         ${CMAKE_CURRENT_BINARY_DIR}/${project_name}-libConfigVersion.cmake
#         VERSION ${PACKAGE_VERSION}
#         COMPATIBILITY SameMajorVersion)

# install(EXPORT ${project_name}-libTargets
#         FILE ${project_name}-libTargets.cmake
#         DESTINATION "lib/cmake/${project_name}-lib")

# configure_package_config_file(
#         cmake/Config.cmake.in ${project_name}-libConfig.cmake
#         INSTALL_DESTINATION "lib/cmake/${project_name}-lib")

# install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${project_name}-libConfig.cmake
#         ${CMAKE_CURRENT_BINARY_DIR}/${project_name}-libConfigVersion.cmake
#         DESTINATION "lib/cmake/${project_name}-lib")
