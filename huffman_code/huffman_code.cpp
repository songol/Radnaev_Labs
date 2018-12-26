#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "huffman_code.hpp"

//#include "binary_heap.hpp"

huffman_code::huffman_code(const char *s1, const char *s2, const char param) {
    data = s1;
    out = s2;
    if (param == 'c') {
        build_frequency_table();
        build_tree();
        std::string code = "";
        int32_t root = tree.size() - 1;
        size_of_tree = 0;
        build_code_table(tree[root], code);
        std::reverse(code_tree.begin(), code_tree.end());

        show_frequency_table();
        show_code_table();
        compress();
    } else {
        decompress();
    }
}

huffman_code::~huffman_code(){
    tree.clear();
    frequency_table.clear();
    code_table.clear();
}

void huffman_code::build_frequency_table() {
    std::ifstream input;
    char let = 'a';
    input.open(data);
    input.get(let);        

    while (!input.eof()) {
            if (frequency_table.find(let) == frequency_table.end()) {
                frequency_table[let] = 1;
            } else {
                frequency_table[let]++;
            }
            input.get(let);        

    }
    input.close();
    numb_of_characters = frequency_table.size();
}

void huffman_code::build_code_table(huffman_node* root, std::string code) {
    if (root->get_left() == std::nullptr_t() && root->get_right() == std::nullptr_t()) {

        std::vector<bool> bool_code;
        for (auto a : code) bool_code.push_back (a == '1');
        code_table[root->get_letter()] = bool_code;
        return;
    }
    if (root->get_left() != std::nullptr_t()) {
        build_code_table(root->get_left(), code + "0");
    }   
    if (root->get_right() != std::nullptr_t()) {
        build_code_table((root->get_right()), code + "1");
//        code_tree.push_back('0');
    }
}

void huffman_code::encode_tree(huffman_node* root) {
    if (root->get_left() == std::nullptr_t() && root->get_right() == std::nullptr_t()) {
        code_tree.push_back('1');
        code_tree.push_back(root->get_letter());
    } else {
        code_tree.push_back('0');
        if (root->get_left() != std::nullptr_t()) {
            encode_tree(root->get_left());
        }
        if (root->get_right() != std::nullptr_t()) {
            encode_tree(root->get_right());
        }
    }
}

void huffman_code::build_tree() {
    std::vector<std::pair<char, int32_t>> freq_vector(frequency_table.begin(), frequency_table.end());
    std::vector<huffman_node*> temp;
    for (auto it = frequency_table.begin(); it != frequency_table.end(); ++it) {
        temp.push_back(new huffman_node(it->first, it->second));
    }
    std::sort(temp.begin(), temp.end(), 
        [](auto &left, auto &right) {
        return left->get_key() > right->get_key();
        } 
    );

    while (temp.size() != 1) {
        int32_t len = temp.size() - 1;
        auto left_node = temp[len];
        auto right_node = temp[len - 1];
        tree.push_back(left_node);
        tree.push_back(right_node);
        auto parent = new huffman_node(left_node, right_node);
        tree.push_back(parent);
        temp.resize(len - 1);
        temp.push_back(parent);
        std::sort(temp.begin(), temp.end(), 
            [](auto &left, auto &right) {
            return left->get_key() > right->get_key();
            } 
        );
    }
    temp.clear();
}

void huffman_code::show_frequency_table() {
    for (auto it = frequency_table.begin(); it != frequency_table.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }
}

void huffman_code::show_code_table() {
    for (auto it = code_table.begin(); it != code_table.end(); ++it) {
        std::cout << it->first << " ";
        for (auto code_bool = (it->second).begin(); 
            code_bool != (it->second).end(); 
            ++code_bool) {
            std::cout << *code_bool;
        }
        std::cout << std::endl;
    }
}

/*void huffman_code::encode_tree(huffman_node* root) {
    char code = 0;
    if (root->get_left() == std::nullptr_t() && 
        root->get_right() == std::nullptr_t()) {
        code = 1;
        output.write((char*) &code, sizeof(char));
        output.write((char*) &(root->get_letter()), sizeof(char));
    } else {
        code = 0;
        output.write(&code, sizeof(char));
        encode_tree(root->get_left(), output);
        encode_tree(root->get_right(), output);
    }
}*/

void huffman_code::compress() {
    encode_tree(tree[tree.size() - 1]);
    size_of_tree = code_tree.size();
    std::ifstream input;
    char let = 'a';
    input.open(data);
    std::ofstream output;   
    output.open(out, std::ios::binary);
    char code = 0;
    int32_t bitcount = 0;
    input.get(let);
    output.write((char*) &numb_of_characters, sizeof(int32_t));
    output.write((char*) &size_of_tree, sizeof(int32_t));
    for (auto it = code_tree.begin(); it != code_tree.end(); ++it) {
        std::cout << *it;
        output.write((char*) &(*it), sizeof(char));
    }
    while (!input.eof()) {
        for (auto it = code_table[let].begin(); it != code_table[let].end(); ++it) {
            if (*it == 0) {
                code = code << 1;
            } else {
                code = (code << 1) | 1;
            }
            bitcount++;
            if (bitcount == 8) {
                output.write(&code, sizeof(char));
                bitcount = 0;
                code = 0;
            }   
        }    
        input.get(let);
    }
    if (bitcount != 0) {
        while (bitcount != 8) {
            code = code << 1;
            bitcount++;
        }
        output.write(&code, sizeof(char));
    }
    output.close();
    input.close();
}

std::vector<bool> huffman_code::char_to_byte(char c){
    std::vector<bool> res(8);
    for (int32_t i = 0; i < 8; ++i) {
        if ((c & (1 << i)) == 0) {
            res[7 - i] = 0;
        } else {
            res[7 - i] = 1;
        }
    }
    return res; 
}

huffman_node* huffman_code::rebuild_tree(char letter) {
    for (int32_t i = 0; i < size_of_tree; ++i) {
        if (letter) {

        }
    }
    std::cout << std::endl;
}


void huffman_code::decompress() {
    std::ifstream input;
    char let = 'a';
    input.open(data, std::ios::in | std::ios::binary);
    input.read((char*) &numb_of_characters, sizeof(int32_t));
    std::cout << numb_of_characters << std::endl;
    input.read((char*) &size_of_tree, sizeof(int32_t));
    std::cout << size_of_tree << std::endl;
    code_tree.resize(size_of_tree, '1');

    for (int32_t i = 0; i < size_of_tree; ++i) {
        //std::cout << i << std::endl;

        input.get(let);
        code_tree[i] = let;
        //input.read((char*) &code_tree[i], sizeof(char));
        std::cout << let << " ";
    }
    std::cout << std::endl;

    rebuild_tree();





    auto search = root;
    input.get(let);
    while (!input.eof()) {
        auto code = char_to_byte(let);
        for (int32_t i = 0; i < 8; ++i) {
            if (search->get_left() == std::nullptr_t() &&
                search->get_right() == std::nullptr_t()) {
                std::cout << search->get_letter();
                search = root;
            } 
            if (code[i] == 1) {
                search = search->get_right();
            } else {
                search = search->get_left();
            }
        }
        input.get(let);
    }
    input.close();
    return;
}
