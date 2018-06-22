cmake_minimum_required(VERSION 3.10)
project(Huffman)

set(CMAKE_CXX_STANDARD 14)

include_directories(${Huffman_SOURCE_DIR})

set(LIB_HEADERS
        lib/headers/huf_types.h
        lib/headers/accumulator.h
        lib/headers/compress.h
        lib/headers/codes.h
        lib/headers/tree.h
        lib/headers/decompress.h
        lib/headers/bit_code.h)

set(LIB_SOURCES
        lib/accumulator.cpp
        lib/compress.cpp
        lib/codes.cpp
        lib/tree.cpp
        lib/decompress.cpp
        lib/bit_code.cpp)

add_library(huf_lib ${LIB_HEADERS} ${LIB_SOURCES})

set(UTILITY_HEADERS
        utility/header/file_reader.h
        utility/header/file_writer.h
        utility/header/file_compress.h
        utility/header/file_decompress.h)

set(UTILITY_SOURCES
        utility/file_reader.cpp
        utility/file_writer.cpp
        utility/file_compress.cpp
        utility/file_decompress.cpp)

add_executable(huf_utility ${UTILITY_HEADERS} ${UTILITY_SOURCES} utility/main.cpp)

target_link_libraries(huf_utility huf_lib)

set(GTEST
        gtest/gtest.h
        gtest/gtest-all.cc
        gtest/gtest_main.cc)

add_executable(huf_test
        ${UTILITY_HEADERS}
        ${UTILITY_SOURCES}
        ${GTEST}
        test/tests.cpp)

target_link_libraries(huf_test huf_lib -lpthread)