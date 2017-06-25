#include "opt_vector.h"
#include <cassert>
#include <iostream>

opt_vector::opt_vector()
    : number(0),
      is_small(false),
      is_empty(true)
{}

opt_vector::opt_vector(size_t sz) : opt_vector() {
        resize(sz);
}

opt_vector::opt_vector(const opt_vector &other) {
    is_small = other.is_small;
    is_empty = other.is_empty;

    if (other.is_small) {
        number = other.number;
    } else {
        new (&long_number) std::shared_ptr<std::vector<uint32_t>>();
        long_number = other.long_number;
    }
}

opt_vector::~opt_vector() {
    if (!is_small && !is_empty) {
        long_number.~shared_ptr<std::vector<uint32_t>>();
    }
}

size_t opt_vector::size() const {
    if (is_empty) {
        return 0;
    } else if (is_small) {
        return 1;
    } else  {
        return long_number->size();
    }
}

void opt_vector::resize(size_t sz) {
    while (size() < sz) {
        push_back(0);
    }
    while (size() > sz) {
        pop_back();
    }
}

uint32_t& opt_vector::operator [](size_t pos) {
    assert(pos < size());
    if (is_small) return number;
    update();
    return (*long_number)[pos];
}

uint32_t const& opt_vector::operator [](size_t pos) const {
    assert(pos < size());
    if (is_small) return number;
    return (*long_number)[pos];
}

opt_vector& opt_vector::operator =(opt_vector const& other) {
    bool original_small = is_small;
    bool original_empty = is_empty;
    is_small = other.is_small;
    is_empty = other.is_empty;

    if (other.is_small) {
        if (!original_small && !original_empty) {
            long_number.~shared_ptr<std::vector<uint32_t>>();
        }
        number = other.number;
    } else {
        if (!original_small && !original_empty && long_number == other.long_number) {
            return *this;
        }
        if (original_small) {
            new (&long_number) std::shared_ptr<std::vector<uint32_t>>();
        }
        long_number = other.long_number;
    }

    return *this;
}

uint32_t& opt_vector::back() {
    assert(!is_empty);
    if (is_small) return number;
    return long_number->back();
}

void opt_vector::push_back(const uint32_t &a) {
    if (is_empty) {
        number = a;
        is_small = true;
        is_empty = false;
    } else {
        if (is_small) {
            uint32_t cur = number;
            new (&long_number) std::shared_ptr<std::vector<uint32_t>>(std::make_shared<std::vector<uint32_t>>());
            long_number->push_back(cur);
            long_number->push_back(a);
            is_small = false;
        } else {
            update();
            long_number->push_back(a);
        }
    }
}

void opt_vector::pop_back() {
    assert(!is_empty);
    if (is_small) {
        is_small = false;
        is_empty = true;
    } else {
        update();
        long_number->pop_back();
        if (long_number->size() == 1) {
            uint32_t cur = (*long_number)[0];
//            long_number.reset();
            long_number.~shared_ptr<std::vector<uint32_t>>();
            number = cur;
            is_small = true;
        }
    }
}

void opt_vector::update() {
    if (is_small) return ;
    if (is_empty) return ;
    if (long_number.unique()) return ;

    std::shared_ptr<std::vector<uint32_t>> long_num = std::make_shared<std::vector<uint32_t>>(*long_number);
    long_number.swap(long_num);
}
