#ifndef HUFFMANTREE
#define HUFFMANTREE

#include <bits/stdc++.h>
#include "encoded_vector.h"

struct huffmantree {

    uint8_t value;
    huffmantree* left;
    huffmantree* right;

    encoded_vector selfcode();
    std::vector<encoded_vector>  code_all();
    huffmantree(uint8_t value, huffmantree* left, huffmantree* right);

private:


    void build_selfcode(encoded_vector& v);
    void build_all_codes(encoded_vector& cur_code, std::vector<encoded_vector>& res);
};

#endif // HUFFMANTREE

