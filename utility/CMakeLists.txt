cmake_minimum_required(VERSION 3.10)
project(HUFFMAN_UTILITY)

set(CMAKE_CXX_STANDARD 14)

include_directories(${HUFFMAN_LIBRARY_SOURCE_DIR}/headers)
include_directories(${HUFFMAN_UTILITY_SOURCE_DIR}/headers)


set(HEADERS )

set(SOURCES
        main.cpp)

add_executable(Huffman ${HEADERS} ${SOURCES})

target_link_libraries(Huffman huf_lib)