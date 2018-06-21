//
// Created by nefed on 19.06.2018.
//

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H


#include "accumulator.h"

struct tree {
    explicit tree(accumulator const &a);

private:
    struct node {
        bool is_leaf;
        node *left, *right;
        symbol my_symbol;
        uint64_t count;

        node(symbol s, uint64_t count);

        node(node *left, node *right);
    } *head;

    friend bool node_comp(const node *a, const node *b);

    friend struct codes;
    friend struct decompress;
};


#endif //HUFFMAN_TREE_H
