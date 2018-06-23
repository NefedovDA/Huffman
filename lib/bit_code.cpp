//
// Created by nefed on 22.06.2018.
//

#include <cassert>
#include "headers/bit_code.h"

void bit_code::push(bit_t b) {
    assert(length < 64);
    if (b) {
        code |= flip;
    }
    flip >>= 1;
    ++length;
}

void bit_code::pop() {
    assert(length != 0);
    flip <<= 1;
    --length;
    if (length != 0) {
        code >>= (64 - length);
        code <<= (64 - length);
    } else {
        code = 0;
    }
}
