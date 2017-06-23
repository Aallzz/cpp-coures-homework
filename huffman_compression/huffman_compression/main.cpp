#include "huffman_coder.h"
#include <algorithm>
#include <queue>
#include <bits/stdc++.h>


std::vector<int32_t> get_frequency(std::istream &fin) {
    std::vector<int32_t> cnt(CODE_SIZE, 0);
    std::vector<uint8_t> buffer;
    while (!fin.eof()) {
        buffer.resize(BLOCK_SIZE);
        fin.read((char*)buffer.data(), BLOCK_SIZE);
        buffer.resize(fin.gcount());

        for (uint8_t cur : buffer) {
            cnt[cur]++;
        }
    }
    fin.clear();
    return cnt;
}

void encode_file(std::istream &fin, std::ostream &fout) {
    std::vector<int32_t> cnt = get_frequency(fin);
    huffman_coder coder(cnt);

    std::vector<uint8_t> buffer;
    std::vector<uint8_t> res;

    size_t huffman_tree_size = coder.get_huffman_tree_size(false);
    fout.write((char*)&huffman_tree_size, 4);
    fout.write((char*)coder.get_huffman_tree_data(), coder.get_huffman_tree_size(true));

    uint64_t file_size = 0ULL;
    fin.seekg(0, fin.end);
    file_size = fin.tellg();
    fin.seekg(0, fin.beg);
    fout.write((char*)&file_size, 8);

    while (!fin.eof()) {
        buffer.resize(BLOCK_SIZE);
        fin.read((char*)buffer.data(), BLOCK_SIZE);
        buffer.resize(fin.gcount());
        res = coder.encode(buffer, false);
        fout.write((char*)res.data(), res.size());
    }
    res = coder.encode(buffer, true);
    fout.write((char*)res.data(), res.size());
}


void decode_file(std::istream &fin, std::ostream &fout) {
    size_t sz_in_bits = 0;
    fin.read((char*)&sz_in_bits, 4);
    std::vector<uint8_t> code(((sz_in_bits + 7) / 8));
    fin.read((char*)code.data(), code.size());
    huffman_coder coder(code, sz_in_bits);

    uint64_t expected_size = 0;
    fin.read((char*)&expected_size, 8);
    std::vector<uint8_t> buffer;
    std::vector<uint8_t> res_buffer;

    while (!fin.eof()) {
        buffer.resize(BLOCK_SIZE);
        fin.read((char*)buffer.data(), BLOCK_SIZE);
        buffer.resize(fin.gcount());

        res_buffer = coder.decode(buffer, expected_size);
        fout.write((char*)res_buffer.data(), res_buffer.size());
        buffer.clear();
        res_buffer.clear();
        if (!expected_size) {
            break;
        }
    }
    assert(expected_size == 0);
}


int main( int argc, char * argv[] )
{
    std::string in;
    std::string out;
    bool encode = true;
    for ( int i = 1 ; i < argc ; ++i ) {
        if (!strcmp("-i", argv[i])) {
            in = argv[++i];
        }
        else if (!strcmp("-o", argv[i])) {
            out = argv[++i];
        } else if (!strcmp("-d", argv[i])) {
            encode = false;
        } else if (!strcmp("-e", argv[i])) {
            encode = true;
        } else if (!strcmp("-h", argv[i])) {
            std::cout << "Program to compress files using Huffman's codes. \n" <<
                    "-i : is used before input file\n" <<
                    "-o : is used before output file\n" <<
                    "-e / -d : encode/decode mode\n" <<
                    "by default program works in encode mode\n";
            return 0;
        } else {
            std::cout << "wrong option" << std::endl;
            return 1;
        }
    }

    std::ifstream fin(in, std::ios::binary);
    std::ofstream fout(out, std::ios::binary);

    if (fin.fail() || fout.fail()) {
        fout << "file problem" << std::endl;
        return 1;
    }

    if (encode) {
        encode_file(fin, fout);
    } else {
        decode_file(fin, fout);
    }

    return 0;
}
