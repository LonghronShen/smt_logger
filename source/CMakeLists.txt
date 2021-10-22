project(smt-logger VERSION 1.0.0)

aux_source_directory(. DIR_SRCS)
add_library(${PROJECT_NAME} STATIC ${DIR_SRCS})

# Add pthread support
find_package(Threads)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

# ------------------------------- install script -------------------------------
# Prepare exposed headers
set(HEADERS ${CMAKE_SOURCE_DIR}/include/smt_logger.h)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include)

# Generate library version info which will generate xxxConfigVersion.cmake,
# the ${PACKAGE_VERSION} is the version defined in project()
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PACKAGE_VERSION}
        COMPATIBILITY SameMajorVersion)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION "lib/cmake/${PROJECT_NAME}")

configure_package_config_file(
        cmake/Config.cmake.in ${PROJECT_NAME}Config.cmake
        INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}")

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION "lib/cmake/${PROJECT_NAME}")
