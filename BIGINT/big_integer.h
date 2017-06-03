#ifndef BIG_INTEGER
#define BIG_INTEGER

#include <cstddef>
#include <iosfwd>
#include <vector>
#include <functional>
#include <cstdint>

class big_integer {

public:
    big_integer(); // done
    big_integer(big_integer const& other); // done
    big_integer(int64_t a); // done
    explicit big_integer(std::string const& str); // done
    ~big_integer(); // done

    big_integer& operator=(big_integer const& other); // done

    big_integer& operator+=(big_integer const& rhs); // done
    big_integer& operator-=(big_integer const& rhs); // done
    big_integer& operator*=(big_integer const& rhs); // done
    big_integer& operator/=(big_integer const& rhs); // done
    big_integer& operator%=(big_integer const& rhs); // done

    big_integer& operator&=(big_integer const& rhs); // done
    big_integer& operator|=(big_integer const& rhs); // done
    big_integer& operator^=(big_integer const& rhs); // done

    big_integer& operator<<=(int rhs); // done
    big_integer& operator>>=(int rhs); // done

    big_integer operator+() const; // done
    big_integer operator-() const; // done
    big_integer operator~() const; // done

    big_integer& operator++(); // done
    big_integer operator++(int); // done

    big_integer& operator--(); // done
    big_integer operator--(int); // done

    friend bool operator==(big_integer const& a, big_integer const& b); // done
    friend bool operator!=(big_integer const& a, big_integer const& b); // done
    friend bool operator<(big_integer const& a, big_integer const& b); // done
    friend bool operator>(big_integer const& a, big_integer const& b); // done
    friend bool operator<=(big_integer const& a, big_integer const& b); // done
    friend bool operator>=(big_integer const& a, big_integer const& b); // done

    friend std::string to_string(big_integer const& a); // done

    big_integer& operator /=(int64_t a); // done
    big_integer& operator *=(int64_t a); // done

    friend big_integer operator *(big_integer a, int b); // done
    friend bool check_big_integer(big_integer const& a);

private:

    std::vector<uint32_t> data;
    bool sign;

    void normalize(big_integer& a) const;
    void add(big_integer &a, big_integer const& b); // done
    void sub(big_integer &a, big_integer const& b); // done
    void multiply(big_integer &a, big_integer const& b); // done

    uint32_t get_digit(size_t pos) const;
    big_integer get_2bit();
    big_integer get_1bit();

    /* Multiple length division helpers */
    big_integer product(big_integer const& y, int64_t k); // done
    big_integer quotient(big_integer const& y, int64_t k); // done
    big_integer remainder(big_integer const& y, int64_t k); // done
    int64_t trial(big_integer const& r, big_integer const& d, size_t k, size_t m);
    bool smaller(big_integer const& r, big_integer const& dq, size_t k, size_t m);
    void difference(big_integer& r, big_integer const& dq, size_t k, size_t m);
    int compare_to(big_integer const& rhs) const; // done
    int compare_absolute_to(big_integer const& rhs) const; // done
    void longdivide(big_integer const& x, big_integer const& y, big_integer& r, big_integer& q, size_t n, size_t m); // done
    void division(big_integer const& x, big_integer const& y, big_integer& q, big_integer& r); // done
    big_integer operation_calc(big_integer const& a, big_integer const& b, std::function<uint32_t (uint32_t, uint32_t)> f); // done
};

big_integer operator+(big_integer a, big_integer const& b); // done
big_integer operator-(big_integer a, big_integer const& b); // done
big_integer operator*(big_integer a, big_integer const& b); // done
big_integer operator/(big_integer a, big_integer const& b); // done
big_integer operator%(big_integer a, big_integer const& b); // done

big_integer operator&(big_integer a, big_integer const& b); // done
big_integer operator|(big_integer a, big_integer const& b); // done
big_integer operator^(big_integer a, big_integer const& b); // done

big_integer operator<<(big_integer a, int b); // done
big_integer operator>>(big_integer a, int b); // done

bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);

std::string to_string(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);

#endif // BIG_INTEGER
