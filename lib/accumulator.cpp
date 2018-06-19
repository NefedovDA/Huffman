//
// Created by nefed on 17.06.2018.
//

#include <cstring>
#include "headers/accumulator.h"

accumulator::accumulator() {
    std::memset(count_table, 0, sizeof(uint64_t) * MAX_SYMBOLS);
}

void accumulator::add_block(std::vector<symbol> const &block) {
    for (auto s : block) {
        ++count_table[s];
    }
}

uint64_t accumulator::get_count(size_t i) {
    return count_table[i];
}
