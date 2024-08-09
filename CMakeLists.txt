cmake_minimum_required(VERSION 3.28)
project(regex C)

set(CMAKE_C_STANDARD 23)

add_compile_options("-O3" "-Os")
add_compile_options("-funsigned-char")
add_compile_options("-Wall" "-Wextra" "-Werror")
if (ENABLE_TEST_COV)
    add_compile_options("-fprofile-arcs" "-ftest-coverage")
endif ()

aux_source_directory(container CONTAINER_SRC)
add_library(container STATIC ${CONTAINER_SRC})

aux_source_directory(grammar GRAMMAR_SRC)
add_library(grammar STATIC ${GRAMMAR_SRC})
target_include_directories(grammar PRIVATE container)
target_link_libraries(grammar PRIVATE container)

aux_source_directory(automaton AUTOMATON_SRC)
add_library(automaton STATIC ${AUTOMATON_SRC})

add_compile_definitions("TARGET_X64" "UNIX64")
aux_source_directory(codegen CODEGEN_SRC)
aux_source_directory(codegen/x64 MCODE_SRC)
add_library(codegen STATIC ${CODEGEN_SRC} ${MCODE_SRC})

add_executable(debug test/debug.c)
target_link_libraries(debug PRIVATE grammar container)

# for tests
link_libraries(grammar automaton)
include_directories(grammar container)

aux_source_directory(test/produce TEST_PRODUCE_SRC)
aux_source_directory(test/tokenize TEST_TOKENIZE_SRC)
add_executable(test-tokenize test/test-tokenize.c ${TEST_TOKENIZE_SRC})
add_executable(test-produce test/test-produce.c ${TEST_PRODUCE_SRC})
add_executable(test-all test/test-all.c ${TEST_TOKENIZE_SRC} ${TEST_PRODUCE_SRC})
target_link_libraries(test-tokenize PRIVATE check)
target_link_libraries(test-produce PRIVATE check)
target_link_libraries(test-all PRIVATE check)
