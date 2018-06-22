//
// Created by nefed on 20.06.2018.
//


#include "header/file_compress.h"
#include "header/file_reader.h"
#include "header/file_writer.h"
#include "lib/headers/accumulator.h"
#include "lib/headers/compress.h"

void file_compress(const char *in_file, const char *out_file) {
    file_reader src(in_file);
    src.check();
    file_writer dst(out_file);
    dst.check();

    accumulator a;
    while (!src.eof()) {
        a.add_block(src.read_symbol_block());
    }
    compress compressor(a);
    src.restart();

    dst.write_table(a);
    dst.write_size(a.get_size());

    while (!src.eof()) {
        dst.write_bit_block(compressor(src.read_symbol_block()));
    }
    dst.flush_bit();
}
