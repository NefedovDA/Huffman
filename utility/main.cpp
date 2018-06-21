#include <iostream>
#include <vector>
#include <cstring>
#include "header/file_compress.h"
#include "header/file_decompress.h"
#include "header/file_writer.h"
#include <ctime>
#include <random>

//uint8_t buf[83886080];
int main(int argc, char **argv) {
    if (argc == 2) {
        if (std::strcmp(argv[1], "-h") != 0) {
            std::cerr << "use -h for help\n";
        } else {
            std::cerr << "-h         : help mode\n";
            std::cerr << "-c SRC DST : compress file SRC and write result to DST\n";
            std::cerr << "-d SRC DST : decompress file SRC and write result to DST\n";
        }
    } else if (argc != 4) {
        std::cerr << "use -h for help\n";
    } else {
        clock_t ts, te;
        if (std::strcmp(argv[1], "-c") == 0) {

            if (std::strcmp(argv[2], argv[3]) == 0) {
                std::cerr << "don't use one file for SRC and DST\n";
                return 0;
            }

            std::cerr << "compressing...\n";
            try {
                ts = clock();
                file_compress(argv[2], argv[3]);
                te = clock();
            } catch (std::runtime_error const &e) {
                std::cerr << "Failed to compress\n" << e.what();
                return 0;
            }

            std::cerr << "finished in " << double(te - ts) / CLOCKS_PER_SEC << " sec\n";
        } else if (std::strcmp(argv[1], "-d") == 0) {

            if (std::strcmp(argv[2], argv[3]) == 0) {
                std::cerr << "don't use one file for SRC and DST\n";
                return 0;
            }

            std::cerr << "decompressing...\n";

            try {
                ts = clock();
                file_decompress(argv[2], argv[3]);
                te = clock();
            } catch (std::runtime_error const &e) {
                std::cerr << "Failed to decompress\n"
                             "problem: " << e.what();
                return 0;
            }

            std::cerr << "finished in " << double(te - ts) / CLOCKS_PER_SEC << " sec\n";
        } else {
            std::cerr << "use -h for help\n";
        }
    }

    /*std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,255);
    for (unsigned char &i : buf) {
        i = dist(gen);
    }
    FILE *out = fopen("../test_files/rand/rand.txt", "wb");

    fwrite(buf, 1, 83886080, out);*/
    return 0;
}

// "-c" "../test_files/1/1.txt" "../test_files/1/1.huf"
// "-d" "../test_files/1/1.huf" "../test_files/1/1ret.txt"

// "-c" "../test_files/3/3.JPG" "../test_files/3/3.huf"
// "-d" "../test_files/3/3.huf" "../test_files/3/3ret.JPG"

// "-c" "../test_files/w_and_p/w_and_p.txt" "../test_files/w_and_p/w_and_p.huf"
// "-d" "../test_files/w_and_p/w_and_p.huf" "../test_files/w_and_p/w_and_pret.txt"

// "-c" "../test_files/rand/rand.txt" "../test_files/rand/rand.huf"
// "-d" "../test_files/rand/rand.huf" "../test_files/rand/rand.txt"