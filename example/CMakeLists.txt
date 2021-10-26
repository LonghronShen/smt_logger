project(${project_name}-exe C CXX)

aux_source_directory(. DIR_SRCS)

add_executable(${project_name}-exe ${DIR_SRCS})

target_link_libraries(${project_name}-exe
    PRIVATE smt-logger-lib)