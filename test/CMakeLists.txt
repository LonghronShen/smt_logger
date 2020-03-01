cmake_minimum_required(VERSION 3.5)

# Set the project name
project(smt_logger_tests C CXX)

#############################################
# Unit tests

# enable CTest testing
enable_testing()

file(GLOB_RECURSE test_src
    ${CMAKE_CURRENT_LIST_DIR}/*.h
    ${CMAKE_CURRENT_LIST_DIR}/*.c
	${CMAKE_CURRENT_LIST_DIR}/*.cc
	${CMAKE_CURRENT_LIST_DIR}/*.cpp
)

# Add a testing executable
add_executable(${CMAKE_PROJECT_NAME} ${test_src})

target_link_libraries(${CMAKE_PROJECT_NAME}
    PUBLIC smt_logger
)

add_test(NAME test_all COMMAND ${CMAKE_PROJECT_NAME})