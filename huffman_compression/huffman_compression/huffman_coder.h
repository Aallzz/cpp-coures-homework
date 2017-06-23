#ifndef HUFFMAN_CODER
#define HUFFMAN_CODER

#include "huffmantree.h"
#include "encoded_vector.h"
#include <vector>
#include <iostream>

constexpr size_t CODE_SIZE = 1 << 8;
constexpr size_t BLOCK_SIZE = 1 << 10;

struct huffman_coder {

    std::vector<uint8_t> encode(std::vector<uint8_t>& buffer, bool ceil);
    std::vector<uint8_t> decode(std::vector<uint8_t>& buffer, uint64_t& expected_size);

    huffman_coder(std::vector<int32_t>& cnt);
    huffman_coder(std::vector<uint8_t>& code, size_t size_in_bits);
    ~huffman_coder();

    size_t get_huffman_tree_size(bool in_bytes);
    uint8_t* get_huffman_tree_data();

    void restore();

private:
    huffmantree *t;
    std::vector<encoded_vector> code;
    encoded_vector encoded_huffmantree;

    huffmantree *root;
    encoded_vector encoded_data;

    huffmantree* create_huffmantree(size_t& pos);
    void clear_tree(huffmantree *&t);

    void build_huffmantree_from_frequency(std::vector<int32_t>& cnt);
    void build_huffmantree_from_code(std::vector<uint8_t>& code, size_t size_in_bits);
};

#endif // HUFFMAN_CODER

