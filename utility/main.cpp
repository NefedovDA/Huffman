#include <iostream>
#include "../lib/headers/accumulator.h"

int main() {
    accumulator my_accumulator;
    std::vector<symbol> block(10, 'a');
    my_accumulator.add_block(block);
    std::cout << my_accumulator.get_count('a');
    return 0;
}