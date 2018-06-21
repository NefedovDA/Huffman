//
// Created by nefed on 20.06.2018.
//

#include "header/file_reader.h"

#define good_size 1024

file_reader::file_reader(const char *file_name) :
        my_file(fopen(file_name, "rb")),
        file_name(file_name) {}

void file_reader::check() {
    if (my_file == nullptr) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "file can not be open or found");
    }
}

std::vector<symbol> file_reader::read_symbol_block() {
    std::vector<symbol> buf(good_size);
    size_t count = fread(&buf[0], sizeof(symbol), good_size, my_file);
    if ((count != good_size && !feof(my_file)) || ferror(my_file)) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "error of reading file");
    }
    buf.resize(count);
    return buf;
}

std::vector<bit_t> file_reader::read_bit_block() {
    uint8_t buf[good_size];
    size_t count = fread(buf, 1, good_size, my_file);
    if ((count != good_size && !feof(my_file)) || ferror(my_file)) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "error of reading file");
    }
    std::vector<bit_t> ret;
    for (size_t i = 0; i < count; ++i) {
        for (size_t j = 128; j > 0; j >>= 1) {
            if ((buf[i] & j) != 0) {
                ret.push_back(1);
            } else {
                ret.push_back(0);
            }
        }
    }
    return ret;
}

void file_reader::read_table(accumulator &a) {
    std::vector<uint64_t> table(MAX_SYMBOL + 1);
    size_t count = fread(&table[0], sizeof(uint64_t), MAX_SYMBOL + 1, my_file);
    if (count != MAX_SYMBOL + 1 || ferror(my_file)) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "error of reading table");
    }
    a.init(table);
}

bool file_reader::eof() {
    return feof(my_file) != 0;
}

void file_reader::restart() {
    rewind(my_file);
}

file_reader::~file_reader() {
    fclose(my_file);
}

uint64_t file_reader::read_in_size() {
    uint64_t size;
    size_t count = fread(&size, sizeof(uint64_t), 1, my_file);
    if (count != 1 || ferror(my_file)) {
        throw std::runtime_error("problem with file '"
                                 + file_name + "' : "
                                 + "error of reading table");
    }
    return size;
}
