//
// Created by nefed on 17.06.2018.
//

#ifndef HAFFMAN_LIBRARY_ACCUMULATOR_H
#define HAFFMAN_LIBRARY_ACCUMULATOR_H

#include <vector>
#include "haf_types.h"


struct accumulator {
    accumulator();

    void add_block(std::vector<symbol> const &block);

    uint64_t get_count(size_t i);

private:
    uint64_t count_table[MAX_SYMBOLS];
};


#endif //HAFFMAN_LIBRARY_ACCUMULATOR_H
