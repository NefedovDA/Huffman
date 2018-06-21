//
// Created by nefed on 19.06.2018.
//

#ifndef HUFFMAN_DECOMPRESS_H
#define HUFFMAN_DECOMPRESS_H

#include "accumulator.h"
#include "tree.h"

// позволяет интерпретировать битовый поток как код Хаффмана на основе таблицы встречаемости (задаётся 1 раз)
struct decompress {
    decompress() = delete;

    explicit decompress(accumulator const &a, uint64_t size);

    std::vector<symbol> operator()(std::vector<bit_t> const &block);

    // позволяет проверить совпал ли конец символьного потока с битовым
    bool empty();

private:
    tree huf_tree;
    tree::node *cur;
    uint64_t size;
};


#endif //HUFFMAN_DECOMPRESS_H
