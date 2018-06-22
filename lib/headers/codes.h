//
// Created by nefed on 17.06.2018.
//

#ifndef HUFFMAN_LIBRARY_CODES_H
#define HUFFMAN_LIBRARY_CODES_H

#include "tree.h"
#include "bit_code.h"

struct codes {
    codes() = delete;

    explicit codes(tree const &t);

    bit_code get(symbol s)const;

    size_t get_length(symbol s) const;

private:
    bit_code code_words_table[MAX_SYMBOL + 1];

    void dfs(tree::node *node, bit_code &cur_code);
};

#endif //HUFFMAN_LIBRARY_CODES_H
