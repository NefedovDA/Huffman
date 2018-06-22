//
// Created by nefed on 22.06.2018.
//

#ifndef HUFFMAN_BIT_CODE_H
#define HUFFMAN_BIT_CODE_H


#include "huf_types.h"

struct bit_code {
    code_len length = 0;
    code_t code = 0;

    bit_code() = default;

    void push(bit_t b);

    void pop();

private:
    code_t flip = 9223372036854775808ULL;
};


#endif //HUFFMAN_BIT_CODE_H
