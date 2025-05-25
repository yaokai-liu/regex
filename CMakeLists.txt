cmake_minimum_required(VERSION 3.28)
project(regex C)

set(CMAKE_C_STANDARD 23)

#add_compile_options("-O3" "-Os")
add_compile_options("-funsigned-char")
add_compile_options("-Wall" "-Wextra" "-Werror")
if (WIN32)
    add_compile_options("-Wno-format")
endif ()
if (ENABLE_TEST_COV)
    add_compile_options("-fprofile-arcs" "-ftest-coverage")
endif ()
if (ENABLE_GPROF)
    add_compile_options("-pg")
    add_link_options("-pg")
endif ()

set(GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/grammar/generated")
if(NOT EXISTS ${GENERATED_DIR})
    message(STATUS "${GENERATED_DIR} doesn't exist, generate grammar action table.")
    execute_process(COMMAND /bin/sh ${CMAKE_CURRENT_SOURCE_DIR}/codegen.sh
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
else()
    message(STATUS "${GENERATED_DIR} exists, skip to generate grammar action table.")
endif()

if (NOT TARGET meman)
    include_directories(meman)
    aux_source_directory(meman MEMAN_SRC)
    add_library(meman STATIC ${MEMAN_SRC})
    link_libraries(meman)
endif ()

include_directories(grammar)
file(GLOB_RECURSE GRAMMAR_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} grammar/*.c grammar/*.h)
add_library(grammar ${GRAMMAR_SRC})
link_libraries(grammar)

add_executable(debug test/debug.c)
target_include_directories(debug PRIVATE grammar)
target_link_libraries(debug PRIVATE grammar)

# for tests

aux_source_directory(test/parse TEST_PRODUCE_SRC)
aux_source_directory(test/tokenize TEST_TOKENIZE_SRC)
add_executable(test-tokenize test/test-tokenize.c ${TEST_TOKENIZE_SRC})
add_executable(test-produce test/test-parse.c ${TEST_PRODUCE_SRC})
add_executable(test-all test/test-all.c ${TEST_TOKENIZE_SRC} ${TEST_PRODUCE_SRC})
target_link_libraries(test-tokenize PRIVATE check)
target_link_libraries(test-produce PRIVATE check)
target_link_libraries(test-all PRIVATE check)
