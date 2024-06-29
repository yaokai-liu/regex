cmake_minimum_required(VERSION 3.28)
project(regex C)

set(CMAKE_C_STANDARD 23)

aux_source_directory(grammar GRAMMAR_SRC)
add_library(regex STATIC ${GRAMMAR_SRC})

include_directories(.)
link_libraries(regex)

add_executable(test-tokenize test/test-tokenize.c)
add_executable(test-produce test/test-produce.c)
