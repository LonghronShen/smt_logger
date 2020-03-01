cmake_minimum_required(VERSION 3.5)

# Set the project name
project(smt-logger-tests C CXX)

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
add_executable(smt-logger-tests ${test_src})

target_link_libraries(smt-logger-tests
    PUBLIC smt-logger-lib
)

add_test(NAME test_all COMMAND smt-logger-tests)