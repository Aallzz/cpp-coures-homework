#ifndef ENCODED_VECTOR
#define ENCODED_VECTOR

#include <vector>
#include <bits/stdc++.h>

struct encoded_vector {

    encoded_vector();
    encoded_vector(size_t sz);
    encoded_vector(std::vector<uint8_t> other, size_t sz);

    void assign(std::vector<uint8_t> other, size_t sz);
    void push_back(bool bit);
    void push_back(uint8_t byte);
    void push_back(encoded_vector const& other);

    void pop_back();

    bool get_bit(size_t pos) const;
    uint8_t get_8bit(size_t pos) const;
    uint8_t get_8bit_from(size_t pos) const;

    void set_bit(size_t pos, bool bit);
    void set_8bit(size_t pos, uint8_t byte);

    void clear();
    void resize(size_t new_sz);
    bool empty() const;
    size_t get_size_8bits(bool ceil) const;
    size_t const& get_size_bits();
    size_t get_size_bits() const;
    uint8_t* data();
    encoded_vector subvector(size_t from, size_t to);

    std::vector<uint8_t> const& get_vector() const;

private:
    size_t sz; // size in bits
    std::vector<uint8_t> v; // encoded vector
};

#endif // ENCODED_VECTOR
