cmake_minimum_required(VERSION 3.28)
project(regex C)

set(CMAKE_C_STANDARD 23)

add_compile_options("-funsigned-char")
add_compile_options("-Wall" "-Wextra" "-Werror")


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

aux_source_directory(test/tokenize TEST_TOKENIZE_SRC)
add_executable(test-tokenize ${TEST_TOKENIZE_SRC})
aux_source_directory(test/produce TEST_PRODUCE_SRC)
add_executable(test-produce ${TEST_PRODUCE_SRC})

target_link_libraries(test-tokenize PRIVATE check)
target_link_libraries(test-produce PRIVATE check)

add_executable(debug debug-token.c)
target_link_libraries(debug PRIVATE grammar container)