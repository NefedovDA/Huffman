//
// Created by nefed on 20.06.2018.
//

#include <cassert>
#include <stdexcept>
#include "header/file_writer.h"

file_writer::file_writer(const char *file_name) :
        my_file(fopen(file_name, "wb")),
        file_name(file_name),
        last_block(0),
        free_bits(64) {}

void file_writer::check() {
    if (my_file == nullptr) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "file can not be open or created");
    }
}

void file_writer::write_table(accumulator const &a) {
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
    fwrite(&block[0], sizeof(symbol), block.size(), my_file);
    if (ferror(my_file)) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "error of writing in file in symbol mode");
    }
}

void file_writer::write_bit_block(std::vector<bit_code> const &block) {
    if (block.empty()) {
        return;
    }
    std::vector<uint64_t> buf;
    buf.reserve(block.size() + 1);
    buf.push_back(last_block);
    for (auto bc : block) {
        if (bc.length <= free_bits) {
            assert(bc.length != 0);
            buf.back() |= (bc.code >> (64 - free_bits));
            free_bits -= bc.length;
        } else {
            if (free_bits != 0) {
                buf.back() |= (bc.code >> (64 - free_bits));
            }
            buf.push_back(bc.code << free_bits);
            free_bits = 64 - (bc.length - free_bits);
        }
    }
    if (free_bits == 0) {
        last_block = 0;
        free_bits = 64;
    } else {
        last_block = buf.back();
        buf.pop_back();
    }
    if (buf.empty()) {
        return;
    }
    fwrite(&buf[0], sizeof(uint64_t), buf.size(), my_file);
    if (ferror(my_file)) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "error of writing in file in bit mode");
    }
}

void file_writer::flush_symbol() {
    fflush(my_file);
    if (ferror(my_file)) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "error of writing in file in symbol mode");
    }
}

void file_writer::flush_bit() {
    if (free_bits != 64) {
        fwrite(&last_block, sizeof(uint64_t), 1, my_file);
        if (ferror(my_file)) {
            throw std::runtime_error("problem with file '"
                                     + file_name + "' : "
                                     + "error of writing in file in bit mode");
        }
    }

}

file_writer::~file_writer() {
    if (my_file != nullptr) {
        fclose(my_file);
    }
}

void file_writer::write_size(uint64_t size) {
    fwrite(&size, sizeof(uint64_t), 1, my_file);
    if (ferror(my_file)) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "error of writing size");
    }
}
