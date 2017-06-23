#include <bits/stdc++.h>
#include "encoded_vector.h"
#include "huffmantree.h"

huffmantree::huffmantree(uint8_t value, huffmantree* left, huffmantree* right)
    : value(value),
      left(left),
      right(right)
{}

encoded_vector huffmantree::selfcode() {
    encoded_vector res;
    build_selfcode(res);
    return res;
}

void huffmantree::build_selfcode(encoded_vector& v) {
    if (left == nullptr && right == nullptr) {
        v.push_back(true); //is leaf
        v.push_back(value);
    } else {
        v.push_back(false);
        left->build_selfcode(v);
        right->build_selfcode(v);
    }
}

std::vector<encoded_vector> huffmantree::code_all() {
    std::vector<encoded_vector> res(256);
    encoded_vector cur_code;
    build_all_codes(cur_code, res);
    return res;
}

void huffmantree::build_all_codes(encoded_vector& cur_code, std::vector<encoded_vector> &res) {
    if (left == nullptr && right == nullptr) {
        res[value] = cur_code;
    } else {
        cur_code.push_back(false);
        left->build_all_codes(cur_code, res);
        cur_code.pop_back();
        cur_code.push_back(true);
        right->build_all_codes(cur_code, res);
        cur_code.pop_back();
    }
}



