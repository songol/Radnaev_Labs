#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include "huffman_code.hpp"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Input error (must be 3 args)"
                << std::endl;
        return 1;
    }
    const char *param = argv[1];
    const char *s1 = argv[2];
    const char *s2 = argv[3];
    auto archive = new huffman_code(s1, s2, param[1]);
    //archive->show_frequency_table();
    //archive->show_code_table();
    //archive->compress();
    //archive->decompress();
}
