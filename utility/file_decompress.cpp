//
// Created by nefed on 20.06.2018.
//

#include <stdexcept>
#include "header/file_decompress.h"
#include "header/file_writer.h"
#include "header/file_reader.h"
#include "lib/headers/decompress.h"

void file_decompress(const char *in_file, const char *out_file) {
    file_reader src(in_file);
    src.check();
    file_writer dst(out_file);
    dst.check();

    accumulator a;
    src.read_table(a);
    decompress decompressor(a, src.read_in_size());

    while (!src.eof()) {
        dst.write_symbol_block(decompressor(src.read_bit_block()));
    }
    dst.flush_symbol();
    if (!decompressor.empty()) {
        throw std::runtime_error("decompressing was finished but data could be incorrect"
                                 "because some dada was not decoding");
    }
    if (!decompressor.is_end()) {
        throw std::runtime_error("decompressing was finished but data could be incorrect"
                                 "only part of data was decoding");
    }
}