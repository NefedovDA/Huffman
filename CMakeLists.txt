cmake_minimum_required(VERSION 3.10)
project(Haffman)

set(CMAKE_CXX_STANDARD 14)

set(LIB_HEADERS
        lib/headers/haf_types.h
        lib/headers/accumulator.h)

set(LIB_SOURCES
        lib/accumulator.cpp )

add_library(huf_lib ${LIB_HEADERS} ${LIB_SOURCES})

set(UTILITY_HEADERS )

set(UTILITY_SOURCES
        utility/main.cpp)

add_executable(huf_utility ${UTILITY_HEADERS} ${UTILITY_SOURCES})

target_link_libraries(huf_utility huf_lib)