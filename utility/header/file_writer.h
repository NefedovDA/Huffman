//
// Created by nefed on 20.06.2018.
//

#ifndef HUFFMAN_FILE_WRITER_H
#define HUFFMAN_FILE_WRITER_H


#include <string>
#include <vector>
#include "lib/headers/accumulator.h"
#include "lib/headers/bit_code.h"

struct file_writer {
    explicit file_writer(const char *file_name);

    void check();

    void write_table(accumulator const &a);

    void write_symbol_block(std::vector<symbol> const &block);

    void write_bit_block(std::vector<bit_code> const &block);

    void write_size(uint64_t size);

    void flush_symbol();

    void flush_bit();

    ~file_writer();

private:
    FILE *my_file;
    std::string file_name;
    uint64_t last_block;
    size_t free_bits;
};


#endif //HUFFMAN_FILE_WRITER_H
