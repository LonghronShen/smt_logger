project(${project_name}-tests C CXX)

enable_testing()

aux_source_directory(. DIR_SRCS)

add_executable(${project_name}-tests ${DIR_SRCS})

target_link_libraries(
  ${project_name}-tests
  PRIVATE smt-logger-lib
  PRIVATE gtest_main)

set_target_properties(
  ${project_name}-tests
  PROPERTIES CXX_STANDARD 20
             CXX_EXTENSIONS OFF
             CXX_STANDARD_REQUIRED ON)

add_test(AllTestsInMain ${project_name}-tests)
