//
// Created by nefed on 19.06.2018.
//

#include "headers/compress.h"

compress::compress(accumulator const &a) :
        codes_table(tree(a)) {}

std::vector<bit_t> compress::operator()(std::vector<symbol> symbols_block) {
    size_t size = 0;
    for (auto s : symbols_block) {
        size += codes_table.get_length(s);
    }
    std::vector<bit_t> buf(size);
    size_t i = 0;
    for (auto s : symbols_block) {
        //std::vector<bit_t> tmp = codes_table.get(s);
        // если символ не встречался, то длина его кода 0 и он игнорируется
        // можно assert(!tmp.empty());
        //buf.reserve(buf.size() + tmp.size());
        //std::copy(tmp.begin(), tmp.end(), std::back_inserter(buf));
        for (auto b : codes_table.get(s)) {
            buf[i] = b;
            ++i;
        }
    }
    return buf;
}

codes compress::get() {
    // возвращаем копию
    return codes_table;
}
