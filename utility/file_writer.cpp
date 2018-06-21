//
// Created by nefed on 20.06.2018.
//

#include "header/file_writer.h"

file_writer::file_writer(const char *file_name) :
        my_file(fopen(file_name, "wb")),
        file_name(file_name),
        flip(0) {}

void file_writer::check() {
    if (my_file == nullptr) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "file can not be open or created");
    }
}

void file_writer::write_table(accumulator const &a) {
    //std::vector<uint64_t> table;
    uint64_t table[MAX_SYMBOL + 1];
    for (symbol s = 0; s < MAX_SYMBOL; ++s) {
        table[s] = a.get_count(s);
    }
    table[MAX_SYMBOL] = a.get_count(MAX_SYMBOL);
    fwrite(&table[0], sizeof(uint64_t), MAX_SYMBOL + 1, my_file);
    if (ferror(my_file)) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "error of writing table");
    }
}

void file_writer::write_symbol_block(std::vector<symbol> const &block) {
    symbol_buf.reserve(symbol_buf.size() + block.size());
    std::copy(block.begin(), block.end(), std::back_inserter(symbol_buf));
    if (symbol_buf.size() >= good_size) {
        fwrite(&symbol_buf[0], sizeof(symbol), symbol_buf.size(), my_file);
        if (ferror(my_file)) {
            throw std::runtime_error("problem with file '"
                                     + file_name + "' : "
                                     + "error of writing in file in symbol mode");
        }
        symbol_buf.clear();
    }
}

void file_writer::write_bit_block(std::vector<bit_t> const &block) {
    for (auto b : block) {
        if (flip == 0) {
            bit_buf.push_back(0);
            flip = 128;
        }
        if (b == 1) {
            bit_buf.back() |= flip;
        }
        flip >>= 1;
        if (bit_buf.size() == good_size && flip == 0) {
            fwrite(&bit_buf[0], 1, good_size, my_file);
            if (ferror(my_file)) {
                throw std::runtime_error("problem with file '"
                                         + file_name + "' : "
                                         + "error of writing in file in bit mode");
            }
            bit_buf.clear();
        }
    }
}

void file_writer::flush_symbol() {
    fwrite(&symbol_buf[0], sizeof(symbol), symbol_buf.size(), my_file);
    if (ferror(my_file)) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "error of writing in file in symbol mode");
    }
}

void file_writer::flush_bit() {
    fwrite(&bit_buf[0], 1, bit_buf.size(), my_file);
    if (ferror(my_file)) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "error of writing in file in bit mode");
    }
}

file_writer::~file_writer() {
    fclose(my_file);
}

void file_writer::write_size(uint64_t size) {
    fwrite(&size, sizeof(uint64_t), 1, my_file);
    if (ferror(my_file)) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "error of writing size");
    }
}
