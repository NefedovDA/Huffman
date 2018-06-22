//
// Created by nefed on 22.06.2018.
//

#include <gtest/gtest.h>
#include <lib/headers/accumulator.h>
#include "../utility/header/file_compress.h"

TEST(correctness, accumulator_test) {
    accumulator a;
    std::vector<symbol> v = {'a', 'b', 'b', 'c', 'c', 'c'};
    for (size_t i = 0; i < 100; ++i) {
        a.add_block(v);
    }
    EXPECT_EQ(a.get_count('a'), 100);
    EXPECT_EQ(a.get_count('b'), 200);
    EXPECT_EQ(a.get_count('c'), 300);
}

TEST(correctness, no_file_test) {
    EXPECT_ANY_THROW(file_compress("no_such_file_1", "no_such_file_2"));
}