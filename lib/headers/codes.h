//
// Created by nefed on 17.06.2018.
//

#ifndef HUFFMAN_LIBRARY_CODES_H
#define HUFFMAN_LIBRARY_CODES_H

#include "huf_types.h"
#include "tree.h"

struct codes {
    codes() = delete;

    explicit codes(tree const &t);

    std::vector<bit_t> get(symbol s)const;

    size_t get_length(symbol s) const;

private:
    std::vector<bit_t> code_words_table[MAX_SYMBOL + 1];

    void dfs(tree::node *node, std::vector<bit_t> &cur_code);
};

#endif //HUFFMAN_LIBRARY_CODES_H
