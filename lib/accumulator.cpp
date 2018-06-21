//
// Created by nefed on 17.06.2018.
//

#include <cstring>
#include <cassert>
#include "headers/accumulator.h"

accumulator::accumulator() :
        size(0) {
    std::memset(count_table, 0, sizeof(uint64_t) * (MAX_SYMBOL + 1));
}

void accumulator::add_block(std::vector<symbol> const &block) {
    for (auto s : block) {
        ++count_table[s];
        ++size;
    }
}

uint64_t accumulator::get_count(symbol s) const {
    return count_table[s];
}

void accumulator::init(std::vector<uint64_t> const &table) {
    assert(table.size() == MAX_SYMBOL + 1);
    for (symbol s = 0; s < MAX_SYMBOL; ++s) {
        count_table[s] += table[s];
        size += table[s];
    }
    count_table[MAX_SYMBOL] += table[MAX_SYMBOL];
    size += table[MAX_SYMBOL];
}

uint64_t accumulator::get_size() {
    return size;
}
