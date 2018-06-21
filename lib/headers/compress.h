//
// Created by nefed on 19.06.2018.
//

#ifndef HUFFMAN_COMPRESS_H
#define HUFFMAN_COMPRESS_H


#include "accumulator.h"
#include "codes.h"

// позволяет сжать блок данных на основе таблицы встречаемости (задаётся 1 раз)
struct compress {
    compress() = delete;

    explicit compress(accumulator const &a);

    std::vector<bit_t> operator()(std::vector<symbol> symbols_block);

    codes get();

private:
    codes codes_table;
};

#endif //HUFFMAN_COMPRESS_H
