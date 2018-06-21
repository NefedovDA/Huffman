//
// Created by nefed on 20.06.2018.
//

#ifndef HUFFMAN_FILE_READER_H
#define HUFFMAN_FILE_READER_H

#include <vector>
#include <cstdio>
#include <string>
#include "../../lib/headers/huf_types.h"
#include "../../lib/headers/accumulator.h"
#include <stdexcept>

struct file_reader {

    explicit file_reader(const char *file_name);

    void check();

    void read_table(accumulator &a);

    std::vector<symbol> read_symbol_block();

    std::vector<bit_t> read_bit_block();

    uint64_t read_in_size();

    bool eof();

    void restart();

    ~file_reader();

private:
    FILE *my_file;
    std::string file_name;
};


#endif //HUFFMAN_FILE_READER_H
