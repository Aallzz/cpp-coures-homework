#include "big_integer.h"
#include <cmath>
#include <cassert>
#include <utility>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdint>


constexpr uint64_t LG = 32LL;
constexpr uint64_t BASE = (1LL << LG);

bool check_big_integer(big_integer const& a){
    for (size_t i = 0; i < a.data.size(); ++i) {
        if (a.data[i] < 0LL) return false;
    }
    return true;
}

uint32_t big_integer::get_digit(size_t pos) const {
    if (pos < 0) return 0;
    if (pos >= data.size()) return 0;
    return data[pos];
}

big_integer::big_integer() {
    sign = false;
    normalize(*this);
    // assert(check_big_integer(*this));
}

big_integer::big_integer(big_integer const& other) :data(other.data), sign(other.sign)
{
    normalize(*this);
    // assert(check_big_integer(*this));
}

big_integer::big_integer(int64_t a) {
    sign = a < 0;
    a = std::abs(a);
    if (a == 0) {
        data.push_back(0);
        return ;
    }
    while (a) {
        data.push_back(a % BASE);
        a /= BASE;
    }
    // assert(check_big_integer(*this));
}

big_integer::~big_integer() {}

big_integer::big_integer(std::string const& str) {
    std::string s = str;
    if (s.length() == 0) {
        big_integer();
    }
    *this = 0;
    big_integer power = 1;
    for (int32_t i = str.size() - 1; i >= (s[0] == '-'); i--) {
        *this += (power * (int64_t)(str[i] - '0'));
        power *= 10;
    }
    sign = s[0] == '-';
    normalize(*this);
    // assert(check_big_integer(*this));
}

int big_integer::compare_absolute_to(big_integer const& rhs) const{
    if (data.size() != rhs.data.size()) return data.size() < rhs.data.size() ? -1 : 1;
    for (int32_t i = data.size() - 1; i >= 0; --i) {
        if (data[i] != rhs.data[i]) return data[i] < rhs.data[i] ? -1 : 1;
    }
    return 0;
}

int big_integer::compare_to(big_integer const& rhs) const {
    if (sign ^ rhs.sign) return sign ? -1 : 1;
    return compare_absolute_to(rhs);
}

void big_integer::add(big_integer& a, big_integer const& b) {
    int64_t carry = 0LL;
    for (size_t i = 0; i < std::max(a.data.size(), b.data.size()) || carry; ++i) {
        if (i == a.data.size()) {
            a.data.push_back(0LL);
        }
        int64_t temp = (int64_t)a.data[i] + (i < b.data.size() ? b.data[i] : 0LL) + carry;
        carry = temp >= BASE;
        if (carry) a.data[i] = (temp - BASE);
        else a.data[i] = temp;
    }
    normalize(a);
    // assert(check_big_integer(a));
}

void big_integer::normalize(big_integer &a) const{
    while (a.data.size() > 0 && a.data.back() == 0) a.data.pop_back();
    if (a.data.size() == 0) {
        a.data.push_back(0);
        a.sign = false;
    }
}

void big_integer::sub(big_integer& a, big_integer const& b) {
    // assert(a.compare_absolute_to(b) >= 0);
    int64_t carry = 0;
    for (size_t i = 0; i < b.data.size() || carry; ++i) {
        int64_t temp = (int64_t)a.data[i] - (i < b.data.size() ? b.data[i] : 0LL) - carry;
        carry = temp < 0LL;
        if (carry) a.data[i] = (BASE + temp);
        else a.data[i] = temp;
    }
    normalize(a);
    // assert(check_big_integer(a));
}

void big_integer::multiply(big_integer& a, big_integer const& b) {
    std::vector<uint32_t> res(a.data.size() + b.data.size());
    for (size_t i = 0; i < a.data.size(); ++i) {
        uint64_t carry = 0LL;
        for (size_t j = 0; j < b.data.size() || carry; ++j) {
            uint64_t temp = res[i + j] + ((uint64_t)a.data[i]) * (j < b.data.size() ? (uint64_t)b.data[j] : 0LL) + carry;
            carry = temp / BASE;
            res[i + j] = temp % BASE;
        }
    }
    a.data = res;
    a.sign = a.sign ^ b.sign;
    normalize(a);
    // assert(check_big_integer(a));
}

big_integer big_integer::product(big_integer const& y, int64_t k) {
    big_integer x = y;
    uint64_t carry = 0LL;
    if (k < 0) {
        k = -k;
        x.sign ^= true;
    }
    for (size_t i = 0; i < x.data.size() || carry; ++i) {
        if (i == x.data.size()) {
            x.data.push_back(0);
        }
        uint64_t temp = (uint64_t)x.data[i] * k + carry;
        carry = temp / BASE;
        x.data[i] = temp % BASE;
    }
    normalize(x);
    // assert(check_big_integer(x));
    return x;
}

big_integer big_integer::quotient(big_integer const& y, int64_t k) {
    big_integer x = y;
    if (k < 0) {
        k = -k;
        x.sign ^= true;
    }
    int64_t carry = 0LL;
    for (int32_t i = x.data.size() - 1; i >= 0; --i) {
        int64_t temp = carry * BASE + x.data[i];
        carry = temp % k;
        x.data[i] = temp / k;
    }
    normalize(x);
    // assert(check_big_integer(x));
    return x;
}

big_integer& big_integer::operator /=(int64_t a) {
    return *this = quotient(*this, a);
}

big_integer& big_integer::operator *=(int64_t a) {
    return *this = product(*this, a);
}

big_integer big_integer::remainder(big_integer const& y, int64_t k) {
    int64_t carry = 0LL;
    for (int32_t i = y.data.size() - 1; i >= 0; --i) {
        carry = (carry * BASE + y.data[i]) % std::abs(k);
    }
    if (y.sign) carry = -carry;
    return big_integer(carry);
}

int64_t big_integer::trial(big_integer const& r, big_integer const& d, size_t k, size_t m) {
    // assert(2 <= m && m <= k + m);
    size_t km = k + m;
    __uint128_t r3 = (static_cast<__uint128_t>(r.get_digit(km)) * BASE + r.get_digit(km - 1)) * BASE + r.get_digit(km - 2);
    __uint128_t d2 = d.get_digit(m - 1) * BASE + d.get_digit(m - 2);
    __uint128_t cur = r3 / d2;
    if (cur >= BASE) return BASE - 1;
    else return cur;
}

bool big_integer::smaller(big_integer const& r, big_integer const& dq, size_t k, size_t m) {
    size_t i = m;
    size_t j = 0;
    while (i != j) {
        if (r.get_digit(i + k) != dq.get_digit(i)) {
            j = i;
        } else {
            i--;
        }
    }
    return r.get_digit(i + k) < dq.get_digit(i);
}

void big_integer::difference(big_integer& r, big_integer const& dq, size_t k, size_t m) {
    int64_t carry = 0LL;
    for (int i = 0; i < m; ++i) {
        if (i + k < r.data.size()) {
            r.data.push_back(0LL);
        }
        int64_t diff = (int64_t)r.data[i + k] - (int64_t)dq.get_digit(i) - carry + BASE;
        r.data[i + k] = diff % BASE;
        carry = 1 - diff / BASE;
    }
    normalize(r);
    // assert(check_big_integer(r));
}

void big_integer::longdivide(big_integer const& x, big_integer const& y,
                             big_integer& q, big_integer& r,
                             size_t n, size_t m) {
    int64_t f = BASE / (y.data[m - 1] + 1);
    r = product(x, f);
    big_integer d = product(y, f);
    big_integer dq;
    q = 0;
    q.data.resize(n - m + 1);
    for (int32_t k = n - m; k >= 0; --k) {
        int64_t qt = trial(r, d, k, m);
        dq = product(d, qt);
        if (smaller(r, dq, k, m)) {
            qt--;
            dq = product(d, qt);
        }
        q.data[k] = qt;
        difference(r, dq, k, m);
    }
    r = quotient(r, f);
    normalize(r);
    normalize(q);
}

void big_integer::division(big_integer const& x, big_integer const& y, big_integer& q, big_integer& r) {
    size_t m = y.data.size();
    if (m == 1) {
        int64_t y1 = (int64_t)y.data[m - 1] * (y.sign ? -1 : 1);
        q = quotient(x, y1);
        r = remainder(x, y1);
    } else {
        size_t n = x.data.size();
        if (m > n) {
            q = 0;
            r = x;
        } else {
            longdivide(x, y, q, r, n, m);
        }
    }
}

big_integer& big_integer::operator /=(big_integer const& rhs) {
    big_integer r, q;
    bool s = this->sign ^ rhs.sign;
    division(*this, rhs, q, r);
    *this = q;
    this->sign = s;
    return *this;
}

big_integer& big_integer::operator%=(big_integer const& rhs) {
    big_integer r, q;
    division(*this, rhs, q, r);
    *this = r;
    return *this;
}

big_integer& big_integer::operator +=(big_integer const& rhs) {
    if (rhs.sign == sign) {
        add(*this, rhs);
    } else {
        if (compare_absolute_to(rhs) >= 0) {
            sub(*this, rhs);
        } else {
            big_integer tmp = rhs;
            sub(tmp, *this);
            std::swap(tmp, *this);
        }
    }
    return *this;
}

big_integer& big_integer::operator -=(big_integer const& rhs) {
    big_integer temp = rhs;
    temp.sign = rhs.sign ^ 1;
    return *this += temp;
}

big_integer& big_integer::operator *=(big_integer const& rhs) {
    multiply(*this, rhs);
    return *this;
}

big_integer& big_integer::operator =(big_integer const& other) {
    this->sign = other.sign;
    this->data = other.data;
    return *this;
}

big_integer& big_integer::operator++() {
    *this += 1;
    return *this;
}

big_integer big_integer::operator++(int) {
    big_integer temp(*this);
    *this += 1;
    return temp;
}

big_integer& big_integer::operator--() {
    *this -= 1;
    return *this;
}

big_integer big_integer::operator--(int) {
    big_integer temp(*this);
    *this -= 1;
    return temp;
}

big_integer big_integer::operation_calc(big_integer const& a, big_integer const& b, std::function<uint32_t (uint32_t, uint32_t)> f) {
    uint32_t p1, p2;
    p1 = p2 = 0;
    big_integer temp = a;
    if (a.sign) temp =temp.get_2bit(), p1 = BASE - 1;
    big_integer temp2 = b;
    if (b.sign) temp2 = temp2.get_2bit(), p2 = BASE - 1;
    for (size_t i = 0; i < std::max(temp.data.size(), temp2.data.size()); ++i) {
        if (i == temp.data.size()) {
            temp.data.push_back(p1);
        }
        temp.data[i] = f(temp.data[i], i < temp2.data.size() ? temp2.data[i] : p2);
    }
//    temp = temp.get_1bit();
    temp.sign = f(a.sign, b.sign);
    if (temp.sign) {
        temp = temp.get_2bit();
    }
    normalize(temp);
    return temp;
}


big_integer& big_integer::operator&=(big_integer const& rhs) {
    return *this = operation_calc(*this, rhs, [](uint32_t x, uint32_t y){return x & y;});
}

big_integer& big_integer::operator|=(big_integer const& rhs) {
    return *this = operation_calc(*this, rhs, [](uint32_t x, uint32_t y){return x | y;});
}

big_integer& big_integer::operator^=(big_integer const& rhs) {
    return *this = operation_calc(*this, rhs, [](uint32_t x, uint32_t y){return x ^ y;});
}


bool operator==(big_integer const& a, big_integer const& b) {
    return a.compare_to(b) == 0;
}

bool operator!=(big_integer const& a, big_integer const& b) {
    return a.compare_to(b) != 0;
}

bool operator<(big_integer const& a, big_integer const& b) {
    return a.compare_to(b) < 0;
}

bool operator>(big_integer const& a, big_integer const& b) {
    return a.compare_to(b) > 0;
}

bool operator<=(big_integer const& a, big_integer const& b) {
    return a.compare_to(b) <= 0;
}

bool operator>=(big_integer const& a, big_integer const& b) {
    return a.compare_to(b) >= 0;
}


big_integer& big_integer::operator <<=(int rhs) {
    int32_t shl = rhs / LG;
    data.resize(shl + data.size());
    for (int i = data.size() - 1; i + shl >= 0; i--) {
        if (i >= 0)
            data[i + shl] = data[i];
        else
            data[i + shl] = 0;
    }
    *this *= (1 << (rhs % LG));
    return *this;
}

big_integer& big_integer::operator >>=(int rhs) {
    if (rhs == 0) return *this;
    int64_t shr = rhs / LG;
    for (size_t i = 0; i + shr < data.size(); ++i) {
        data[i] = data[i + shr];
    }
    data.resize(data.size() - shr);
    if (this->sign) {
        *this -= (1LL << (rhs % LG)) - 1;
    }
    *this /= (1LL << (rhs % LG));
    return *this;
}

big_integer operator * (big_integer a, int b) {
    // assert(check_big_integer(a));
    return a *= b;
}

big_integer big_integer::operator+() const {
    return *this;
}

big_integer big_integer::operator-() const {
    big_integer temp(*this);
    temp.sign ^= true;
    normalize(temp);
    return temp;
}

big_integer big_integer::get_2bit() {
    big_integer temp(*this);
    temp.sign = false;
    for (size_t i = 0; i < temp.data.size(); ++i) {
        temp.data[i] = ~temp.data[i];
    }
    temp++;
    temp.sign ^= true;
    return temp;
}

big_integer big_integer::operator~() const{
    return -*this - 1;
}

big_integer operator+(big_integer a, big_integer const& b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const& b) {
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const& b) {
    return a *= b;
}

big_integer operator/(big_integer a, big_integer const& b) {
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const& b) {
    return a %= b;
}

big_integer operator&(big_integer a, big_integer const& b) {
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const& b) {
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const& b) {
    return a ^= b;
}

big_integer operator<<(big_integer a, int b) {
    return a <<= b;
}

big_integer operator>>(big_integer a, int b) {
    return a >>= b;
}

std::string to_string(big_integer const &a)
{
    std::string ret = "";
    big_integer ten = 10;
    big_integer zero = 0LL;
    big_integer t = a, temp;
    t.sign = false;
    while (t != 0) {
        temp = (t % 10);
        ret = ret + (char) ((temp.data.size() != 0 ? temp.data[0] : 0)+ '0');
        t /= 10;
    }
    std::reverse(ret.begin(), ret.end());
    if (a.sign && ret != "")
        ret = "-" + ret;
    if (ret == "")
        ret = "0";
    return ret;
}

std::ostream& operator<<(std::ostream& s, big_integer const& a) {
    return s << to_string(a);
}
