//
// Created by nefed on 17.06.2018.
//

#ifndef HUFFMAN_LIBRARY_ACCUMULATOR_H
#define HUFFMAN_LIBRARY_ACCUMULATOR_H

#include <vector>
#include "huf_types.h"

// класс накопител, т. к. необходимо обробатывать очень большие файлы
struct accumulator {
    accumulator();

    void add_block(std::vector<symbol> const &block);

    void init(std::vector<uint64_t> const &table);

    uint64_t get_count(symbol s) const;

    uint64_t get_size();

private:
    uint64_t count_table[MAX_SYMBOL + 1];
    uint64_t size;
};


#endif //HUFFMAN_LIBRARY_ACCUMULATOR_H
