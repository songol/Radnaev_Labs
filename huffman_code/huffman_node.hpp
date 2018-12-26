#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

class huffman_node {
private:
    std::vector<huffman_node*> tree;
    int32_t key;
    char letter;
    std::string code;
    huffman_node *left, *right;
public:
    huffman_node();
    huffman_node(char letter, int32_t key);
    huffman_node(huffman_node* left, huffman_node* right);
    huffman_node(const huffman_node& node);    
    ~huffman_node();
    int32_t get_key() {return key;};
    char get_letter() {return letter;};
    std::string get_code() {return code;};
    huffman_node* get_left() {return left;};
    huffman_node* get_right() {return right;};
};
#endif // HUFFMAN_NODE