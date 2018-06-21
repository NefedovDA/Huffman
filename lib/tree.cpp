//
// Created by nefed on 19.06.2018.
//

#include <algorithm>
#include <stdexcept>
#include "headers/tree.h"

bool node_comp(const tree::node *a, const tree::node *b) {
    return a->count > b->count;
}

tree::tree(accumulator const &a) {
    std::vector<node *> v;
    for (symbol s = 0; s < MAX_SYMBOL; ++s) {
        if (a.get_count(s) != 0) {
            v.push_back(new node(s, a.get_count(s)));
        }
    }
    if (a.get_count(MAX_SYMBOL) != 0) {
        v.push_back(new node(MAX_SYMBOL, a.get_count(MAX_SYMBOL)));
    }
    if (v.empty()) {
        head = nullptr;
    } else {
        while (v.size() != 1) {
            std::sort(v.begin(), v.end(), node_comp);
            auto tmp = new node(v[v.size() - 2], v[v.size() - 1]);
            v.pop_back();
            v.pop_back();
            v.push_back(tmp);
        }
        head = v[0];
    }
}

tree::node::node(symbol s, uint64_t count) :
        is_leaf(true),
        left(nullptr),
        right(nullptr),
        my_symbol(s),
        count(count) {}

tree::node::node(tree::node *left, tree::node *right) :
        is_leaf(false),
        left(left),
        right(right),
        my_symbol(0),
        count(left->count + right->count) {}
