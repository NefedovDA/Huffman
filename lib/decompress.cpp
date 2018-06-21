//
// Created by nefed on 19.06.2018.
//

#include "headers/decompress.h"

decompress::decompress(accumulator const &a, uint64_t size) :
        huf_tree(a),
        cur(huf_tree.head),
        size(size) {}

std::vector<symbol> decompress::operator()(std::vector<bit_t> const &block) {
    std::vector<symbol> buf;
    for (auto b : block) {
        if (b) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }

        if (cur->is_leaf) {
            buf.push_back(cur->my_symbol);
            cur = huf_tree.head;
            --size;
            if (size == 0) {
                return buf;
            }
        }
    }
    return buf;
}

bool decompress::empty() {
    return cur == huf_tree.head;
}
