//
// Created by nefed on 19.06.2018.
//

#include "headers/compress.h"

compress::compress(accumulator const &a) :
        codes_table(tree(a)) {}

std::vector<bit_code> compress::operator()(std::vector<symbol> symbols_block) {
    std::vector<bit_code> buf(symbols_block.size());
    for (size_t i = 0; i < symbols_block.size(); ++i) {
        // если символ не встречался, то длина его кода 0 и он игнорируется
        // можно assert(!tmp.empty());
        buf[i] = codes_table.get(symbols_block[i]);
    }
    return buf;
}

codes compress::get() {
    // возвращаем копию
    return codes_table;
}
