//
// Created by nefed on 17.06.2018.
//

#include "headers/codes.h"

codes::codes(tree const &t) {
    if (t.head != nullptr) {
        if (t.head->is_leaf) {
            code_words_table[t.head->my_symbol].push(0);
        } else {
            bit_code v;
            dfs(t.head, v);
        }
    }
}

bit_code codes::get(symbol s)const {
    // если символ не встречался, то его код длины 0
    return code_words_table[s];
}

void codes::dfs(tree::node *node, bit_code &cur_code) {
    if (node->is_leaf) {
        code_words_table[node->my_symbol] = cur_code;
    } else {
        cur_code.push(0);
        dfs(node->left, cur_code);
        cur_code.pop();
        cur_code.push(1);
        dfs(node->right, cur_code);
        cur_code.pop();
    }
}

size_t codes::get_length(symbol s) const {
    return code_words_table[s].length;
}
