#ifndef BIG_INTEGER
#define BIG_INTEGER

#include <cstddef>
#include <iosfwd>
#include <vector>
#include <functional>
#include <cstdint>
#include "opt_vector.h"

class big_integer {

public:
    big_integer();
    big_integer(big_integer const& other);
    big_integer(int64_t a);
    explicit big_integer(std::string const& str);
    ~big_integer();

    big_integer& operator=(big_integer const& other);

    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);
    big_integer& operator*=(big_integer const& rhs);
    big_integer& operator/=(big_integer const& rhs);
    big_integer& operator%=(big_integer const& rhs);

    big_integer& operator&=(big_integer const& rhs);
    big_integer& operator|=(big_integer const& rhs);
    big_integer& operator^=(big_integer const& rhs);

    big_integer& operator<<=(int rhs);
    big_integer& operator>>=(int rhs);

    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;

    big_integer& operator++();
    big_integer operator++(int);

    big_integer& operator--();
    big_integer operator--(int);

    friend bool operator==(big_integer const& a, big_integer const& b);
    friend bool operator!=(big_integer const& a, big_integer const& b);
    friend bool operator<(big_integer const& a, big_integer const& b);
    friend bool operator>(big_integer const& a, big_integer const& b);
    friend bool operator<=(big_integer const& a, big_integer const& b);
    friend bool operator>=(big_integer const& a, big_integer const& b);

    friend std::string to_string(big_integer const& a);

    big_integer& operator /=(int64_t a);
    big_integer& operator *=(int64_t a);

    friend big_integer operator *(big_integer a, int b);
    friend bool check_big_integer(big_integer const& a);

private:

    opt_vector data;
    bool sign;

    void normalize(big_integer& a) const;
    void add(big_integer &a, big_integer const& b);
    void sub(big_integer &a, big_integer const& b);
    void multiply(big_integer &a, big_integer const& b);

    uint32_t get_digit(size_t pos) const;
    big_integer get_2bit();

    /* Multiple length division helpers */
    big_integer product(big_integer const& y, int64_t k);
    big_integer quotient(big_integer const& y, int64_t k);
    big_integer remainder(big_integer const& y, int64_t k);
    int64_t trial(big_integer const& r, big_integer const& d, size_t k, size_t m);
    bool smaller(big_integer const& r, big_integer const& dq, size_t k, size_t m);
    void difference(big_integer& r, big_integer const& dq, size_t k, size_t m);
    int compare_to(big_integer const& rhs) const;
    int compare_absolute_to(big_integer const& rhs) const;
    void longdivide(big_integer const& x, big_integer const& y, big_integer& r, big_integer& q, size_t n, size_t m);
    void division(big_integer const& x, big_integer const& y, big_integer& q, big_integer& r);

    big_integer operation_calc(big_integer const& a, big_integer const& b, std::function<uint32_t (uint32_t, uint32_t)> f);
};

big_integer operator+(big_integer a, big_integer const& b);
big_integer operator-(big_integer a, big_integer const& b);
big_integer operator*(big_integer a, big_integer const& b);
big_integer operator/(big_integer a, big_integer const& b);
big_integer operator%(big_integer a, big_integer const& b);

big_integer operator&(big_integer a, big_integer const& b);
big_integer operator|(big_integer a, big_integer const& b);
big_integer operator^(big_integer a, big_integer const& b);

big_integer operator<<(big_integer a, int b);
big_integer operator>>(big_integer a, int b);

bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);

std::string to_string(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);

#endif // BIG_INTEGER
