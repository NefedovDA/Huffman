//
// Created by nefed on 22.06.2018.
//

#include <gtest/gtest.h>
#include <lib/headers/accumulator.h>
#include <lib/headers/bit_code.h>
#include <lib/headers/codes.h>
#include <utility/header/file_decompress.h>
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

TEST(correctness, bit_code_test) {
    bit_code bc;
    for (size_t i = 0; i < 64; ++i) {
        bc.push(1);
    }
    EXPECT_EQ(bc.length, 64);
    EXPECT_EQ(bc.code, 18446744073709551615ULL);
    for (size_t i = 0; i < 64; ++i) {
        bc.pop();
    }
    EXPECT_EQ(bc.length, 0);
    EXPECT_EQ(bc.code, 0);
}

TEST(correctness, codes_and_tree_test) {
    accumulator a;
    a.add_block({'a',
                 'b', 'b',
                 'c', 'c', 'c', 'c',
                 'd', 'd', 'd', 'd', 'd', 'd', 'd', 'd'});
    tree t(a);
    codes cd(t);
    EXPECT_EQ(cd.get('a').code, 7ULL << 61);
    EXPECT_EQ(cd.get('b').code, 3ULL << 62);
    EXPECT_EQ(cd.get('c').code, 1ULL << 63);
    EXPECT_EQ(cd.get('d').code, 0ULL);
}

TEST(correctness, no_file_test) {
    EXPECT_ANY_THROW(file_compress("no_such_file", "../test_files/1/1.huf"));

    EXPECT_ANY_THROW(file_decompress("no_such_file", "../test_files/1/1ret.txt"));
}

bool check_file_equals(const char *f_file_name, const char *s_file_name) {
    FILE *f_file = fopen(f_file_name, "rb");
    assert(f_file != nullptr);
    FILE *s_file = fopen(s_file_name, "rb");
    assert(s_file != nullptr);

    std::vector<uint8_t> f_buf(128);
    std::vector<uint8_t> s_buf(128);

    while (!feof(f_file) && !feof(s_file)) {
        fread(&f_buf[0], sizeof(uint8_t), 128, f_file);
        fread(&s_buf[0], sizeof(uint8_t), 128, s_file);
        if (f_buf != s_buf) {
            return false;
        }
    }
    return (feof(f_file) && feof(s_file));
}

TEST(correctness, zero_file_test) {
    file_compress("../test_files/0/0.txt", "../test_files/0/0.huf");
    file_decompress("../test_files/0/0.huf", "../test_files/0/0ret.txt");

    EXPECT_TRUE(check_file_equals("../test_files/0/0.txt", "../test_files/0/0ret.txt"));
}

TEST(correctness, lonely_symbol_file_test) {
    file_compress("../test_files/4/4.txt", "../test_files/4/4.huf");
    file_decompress("../test_files/4/4.huf", "../test_files/4/4ret.txt");

    EXPECT_TRUE(check_file_equals("../test_files/4/4.txt", "../test_files/4/4ret.txt"));
}

TEST(correctness, hello_world_test) {
    file_compress("../test_files/1/1.txt", "../test_files/1/1.huf");
    file_decompress("../test_files/1/1.huf", "../test_files/1/1ret.txt");

    EXPECT_TRUE(check_file_equals("../test_files/1/1.txt", "../test_files/1/1ret.txt"));
}

TEST(correctness, UTF8_test) {
    file_compress("../test_files/2/2.txt", "../test_files/2/2.huf");
    file_decompress("../test_files/2/2.huf", "../test_files/2/2ret.txt");

    EXPECT_TRUE(check_file_equals("../test_files/2/2.txt", "../test_files/2/2ret.txt"));
}

TEST(correctness, JPG_test) {
    file_compress("../test_files/3/3.JPG", "../test_files/3/3.huf");
    file_decompress("../test_files/3/3.huf", "../test_files/3/3ret.JPG");

    EXPECT_TRUE(check_file_equals("../test_files/3/3.JPG", "../test_files/3/3ret.JPG"));
}
TEST(correctness, w_and_p_test) {
    file_compress("../test_files/w_and_p/w_and_p.txt", "../test_files/w_and_p/w_and_p.huf");
    file_decompress("../test_files/w_and_p/w_and_p.huf", "../test_files/w_and_p/w_and_pret.txt");

    EXPECT_TRUE(check_file_equals("../test_files/w_and_p/w_and_p.txt", "../test_files/w_and_p/w_and_pret.txt"));
}
TEST(correctness, rand_test) {
    file_compress("../test_files/rand/rand.txt", "../test_files/rand/rand.huf");
    file_decompress("../test_files/rand/rand.huf", "../test_files/rand/randret.txt");

    EXPECT_TRUE(check_file_equals("../test_files/rand/rand.txt", "../test_files/rand/randret.txt"));
}