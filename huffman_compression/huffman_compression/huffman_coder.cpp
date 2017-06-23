#include "huffmantree.h"
#include "encoded_vector.h"
#include "huffman_coder.h"
#include <queue>
#include <algorithm>

huffman_coder::huffman_coder(std::vector<int32_t> &array) {
    build_huffmantree_from_frequency(array);
}

huffman_coder::huffman_coder(std::vector<uint8_t> &code, size_t size_in_bits) {
    build_huffmantree_from_code(code, size_in_bits);
}

huffman_coder::~huffman_coder() {
    clear_tree(t);
}

void huffman_coder::clear_tree(huffmantree *&t) {
    if (t->left) clear_tree(t->left);
    if (t->right) clear_tree(t->right);
    delete t;
}

void huffman_coder::build_huffmantree_from_frequency(std::vector<int32_t> &cnt) {
    std::priority_queue<std::pair<int32_t, huffmantree*>> q;

    for (size_t i = 0; i < CODE_SIZE; ++i) {
        if (cnt[i] == 0) continue;
        q.push({-cnt[i], new huffmantree(i, nullptr, nullptr)});
    }

    if (q.empty()) {
        t = root = nullptr;
        return ;
    }

    while (q.size() != 1) {
        auto left = q.top(); q.pop();
        auto right = q.top(); q.pop();
        q.push({-(-left.first + -right.first), new huffmantree(0, right.second, left.second)});
    }

    t = q.top().second; q.pop();
    code = t->code_all();
    encoded_huffmantree = t->selfcode();
    root = t;
}

void huffman_coder::build_huffmantree_from_code(std::vector<uint8_t> &code, size_t size_in_bits) {
    encoded_huffmantree.assign(code, size_in_bits);
    size_t pos = 0;
    t = create_huffmantree(pos);
    assert(pos == encoded_huffmantree.get_size_bits());
    root = t;
}

huffmantree* huffman_coder::create_huffmantree(size_t& pos) {
    assert(pos < encoded_huffmantree.get_size_bits());
    bool cur_bit = encoded_huffmantree.get_bit(pos++);
    if (cur_bit) {
        uint8_t cur_byte = encoded_huffmantree.get_8bit_from(pos);
        pos += 8;
        return new huffmantree(cur_byte, nullptr, nullptr);
    } else {
       return new huffmantree(0, create_huffmantree(pos), create_huffmantree(pos));
    }
}

size_t huffman_coder::get_huffman_tree_size(bool in_bytes) {
    return in_bytes ? encoded_huffmantree.get_size_8bits(true) : encoded_huffmantree.get_size_bits();
}

uint8_t* huffman_coder::get_huffman_tree_data() {
    return encoded_huffmantree.data();
}

std::vector<uint8_t> huffman_coder::encode(std::vector<uint8_t> &buffer, bool ceil) {
    for (uint8_t cur : buffer) {
        assert(cur >= 0 && cur < CODE_SIZE);
        encoded_data.push_back(code[cur]);
    }

    std::vector<uint8_t> res = encoded_data.get_vector();
    res.resize(encoded_data.get_size_8bits(ceil));

    encoded_data = encoded_data.subvector(
                encoded_data.get_size_8bits(false) << 3,
                encoded_data.get_size_bits());

    return res;
}

std::vector<uint8_t> huffman_coder::decode(std::vector<uint8_t>& buffer, uint64_t &expected_size) {
    std::vector<uint8_t> res_buffer;
    for (uint8_t byte : buffer) {
        for (size_t i = 0; i < 8 && expected_size; ++i) {
                if ((byte >> i) & 1) {
                    t = t->right;
                } else {
                    t = t->left;
                }
                if (t->left == nullptr && t->right == nullptr) {
                    res_buffer.push_back(t->value);
                    t = root;
                    expected_size--;
                }
                assert(t->value == 0 && t->left && t->right);
        }
        if (!expected_size) {
           break;
        }
    }
    return res_buffer;
}

void huffman_coder::restore() {
    t = root;
    encoded_data.clear();
}
