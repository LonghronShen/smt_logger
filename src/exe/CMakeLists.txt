project(smt-logger-exe CXX)

file(GLOB_RECURSE src
  ${CMAKE_CURRENT_LIST_DIR}/*.h
  ${CMAKE_CURRENT_LIST_DIR}/*.hpp

  ${CMAKE_CURRENT_LIST_DIR}/*.c
  ${CMAKE_CURRENT_LIST_DIR}/*.cc
  ${CMAKE_CURRENT_LIST_DIR}/*.cpp
)

add_executable(smt-logger-exe ${src})

target_link_libraries(smt-logger-exe
    PUBLIC smt-logger-lib)