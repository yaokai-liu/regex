cmake_minimum_required(VERSION 3.28)
project(regex C)

set(CMAKE_C_STANDARD 23)

aux_source_directory(container CONTAINER_SRC)
add_library(container STATIC ${CONTAINER_SRC})

aux_source_directory(grammar GRAMMAR_SRC)
add_library(grammar STATIC ${GRAMMAR_SRC})
target_include_directories(grammar PRIVATE container)
target_link_libraries(grammar PRIVATE container)

aux_source_directory(automaton AUTOMATON_SRC)
add_library(automaton STATIC ${AUTOMATON_SRC})


# for tests
link_libraries(grammar automaton)
include_directories(grammar container)
add_executable(test-tokenize test/test-tokenize.c)
add_executable(test-produce test/test-produce.c)
