cmake_minimum_required(VERSION 3.10)
project(HAFFMAN_LIBRARY)

set(CMAKE_CXX_STANDARD 14)

include_directories(${HUFFMAN_LIBRARY_SOURCE_DIR}/headers)

set(LIB_HEADERS
        headers/haf_types.h
        headers/accumulator.h)

set(LIB_SOURCES
        accumulator.cpp )

add_library(huf_lib ${LIB_HEADERS} ${LIB_SOURCES})