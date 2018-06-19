//
// Created by nefed on 17.06.2018.
//

#include <cstring>
#include <cassert>
#include "headers/codes.h"

codes::codes(tree data) {
    std::memset(length_table, 0, sizeof(code_len) * MAX_SYMBOLS);

}

std::pair<code, code_len> codes::get(symbol symb) {
    assert(length_table[symb] != 0);
    return {code_table[symb], length_table[symb]};
}
