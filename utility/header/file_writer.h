//
// Created by nefed on 20.06.2018.
//

#ifndef HUFFMAN_FILE_WRITER_H
#define HUFFMAN_FILE_WRITER_H


#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>
#include "../../lib/headers/huf_types.h"
#include "../../lib/headers/accumulator.h"
#include <stdexcept>

struct file_writer {
    explicit file_writer(const char *file_name);

    void check();

    void write_table(accumulator const &a);

    void write_symbol_block(std::vector<symbol> const &block);

    void write_bit_block(std::vector<bit_t> const &block);

    void write_size(uint64_t size);

    void flush_symbol();

    void flush_bit();

    ~file_writer();

private:
    FILE *my_file;
    std::string file_name;
    std::vector<uint8_t> bit_buf;
    uint8_t flip;
    std::vector<symbol> symbol_buf;

    static const size_t good_size = 128;
};


#endif //HUFFMAN_FILE_WRITER_H
