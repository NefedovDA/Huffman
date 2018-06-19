//
// Created by nefed on 17.06.2018.
//

#ifndef HAFFMAN_LIBRARY_CODES_H
#define HAFFMAN_LIBRARY_CODES_H

#include <utility>
#include "haf_types.h"
#include "tree.h"

struct codes {
    codes() = delete;

    explicit codes(tree data);

    std::pair<code, code_len> get(symbol symb);

private:
    code code_table[MAX_SYMBOLS];
    code_len length_table[MAX_SYMBOLS];
};


#endif //HAFFMAN_LIBRARY_CODES_H
