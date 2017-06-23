#include "encoded_vector.h"
#include <vector>

encoded_vector::encoded_vector() : sz(0) {}

encoded_vector::encoded_vector(size_t size_in_bits) {
    sz = size_in_bits;
    v.resize(sz >> 8);
}

encoded_vector::encoded_vector(std::vector<uint8_t> other, size_t sz)
    : sz(sz),
      v(other)
{}

void encoded_vector::assign(std::vector<uint8_t> other, size_t sz) {
    v = other;
    this->sz = sz;
}

void encoded_vector::push_back(bool bit) {
    if ((sz & 7) == 0) {
        v.push_back(bit);
    } else {
        v.back() |= (bit << (sz & 7));
    }
    sz++;
}

void encoded_vector::push_back(uint8_t byte) {
    for (int i = 0; i < 8; ++i) {
        push_back((bool)(byte & 1));
        byte >>= 1;
    }
}

void encoded_vector::push_back(encoded_vector const& other) {
    for (size_t i = 0; i < other.get_size_8bits(false); ++i) {
        push_back(other.get_8bit(i));
    }
    for (size_t i = other.get_size_8bits(false) << 3; i < other.sz; ++i) {
        push_back(other.get_bit(i));
    }
}

void encoded_vector::pop_back() {
    assert(sz > 0);
    --sz;
    v.back() &= ~(1 << (sz & 7));
    if ((sz & 7) == 0) v.pop_back();
}

bool encoded_vector::get_bit(size_t pos) const {
    return (v[pos >> 3] >> (pos & 7)) & 1;
}

uint8_t encoded_vector::get_8bit(size_t pos) const {
    return v[pos];
}

uint8_t encoded_vector::get_8bit_from(size_t pos) const {
    uint8_t res = 0;
    for (size_t p = 0; p < 8; ++p) {
        res |= (get_bit(pos + p) << p);
    }
    return res;
}

void encoded_vector::set_bit(size_t pos, bool bit) {
    assert(pos < sz);
    bool cur_bit = get_bit(pos);
    if (cur_bit != bit) {
        v[pos >> 3] ^= (1 << (pos & 7));
    }
}

void encoded_vector::set_8bit(size_t pos, uint8_t byte) {
    assert(pos < v.size());
    v[pos] = byte;
}

void encoded_vector::clear() {
    sz = 0;
    v.clear();
}

void encoded_vector::resize(size_t new_sz) {
    sz = new_sz;
    v.resize((sz >> 3) + (sz % 8 != 0));
}

size_t encoded_vector::get_size_8bits(bool ceil) const {
    if (ceil) return v.size();
    else return sz >> 3;
}

size_t const& encoded_vector::get_size_bits()  {
    return sz;
}

size_t encoded_vector::get_size_bits() const {
    return sz;
}


uint8_t* encoded_vector::data() {
    return v.data();
}

std::vector<uint8_t> const& encoded_vector::get_vector() const {
    return v;
}

encoded_vector encoded_vector::subvector(size_t from, size_t to) {
    assert(from <= to);
    assert(from >= 0);
    assert(from <= sz);
    assert(to >= 0);
    assert(to <= sz);

    encoded_vector res;

    while (from % 8 != 0 && from < to) {
        res.push_back(get_bit(from++));
    }
    while (from + 8 < to) {
        res.push_back(get_8bit(from >> 3));
        from += 8;
    }
    while (from < to) {
        res.push_back(get_bit(from++));
    }

    return res;
}
