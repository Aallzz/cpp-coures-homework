#include <iostream>
#include <string>
#include "big_integer.h"
#include <cassert>
#include <bits/stdc++.h>

using namespace std;

//big_integer cur;

string gen_random_string(int k) {
    string res;
    if (rand() % 2 == 0) res += '-';
    res += char((int)'1' + rand() % 9);
    for (int i = 0; i < k *2 ; ++i) {
        res += ('0' + rand() % 10);
    }
    return res;
}

int myrand()
{
    int val = rand() - RAND_MAX / 2;
    if (val != 0)
        return val;
    else
        return 1;
}

int main() {

    big_integer a("-1125899906842624");
    big_integer b("3335378661");

//    big_integer a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
//    big_integer b(                                                     "100000000000000000000000000000000000000");
//    big_integer c( "-999999999999999999999999999999999999999999999999999900000000000000000000000000000000000000");


    big_integer p = a >> 41;
    cout << p << endl;
//    p >>= 31;
    cout << a << endl;
    cout << b << endl;
    cout << p << endl;

//    big_integer a = 2;
//    big_integer b = 2;

//    bool p = (a == b);
//    cout << p << endl;
//
//    int aa = -1234;
//    int bb = aa >> 3;
//
//    cout << aa << " " << bb << endl;
//
//    big_integer c = a + b;
//
//
//    cout << c << endl;
//    cout << ((-155) >>  3) << endl;
//    cout << a << endl;
//    big_integer res = a % b;



//    for (int i = -100; i < 100; ++i) {
//        long long aa = i * (rand() / 100);
//        int c = rand() % 20;
//        big_integer cur = aa;
//        big_integer p = cur >> c;
//        int bb = aa >> c;

//        if (p != bb) {
//            p = cur >> c;
//            cout << "a = " << aa << " " << cur << endl;
//            cout << "c = " << c << endl;
//            cout << "res = " << bb << " " << p << endl;
//            cout << endl;
//        }
//    }

//    for (unsigned itn = 0; itn != 1000; ++itn)
//    {
//        std::vector<int> multipliers;
//
//        for (size_t i = 0; i != 3; ++i)
//            multipliers.push_back(myrand());
//
//        big_integer accumulator = 1;
//
//        for (size_t i = 0; i != 3; ++i)
//            accumulator *= multipliers[i];
//
//        random_shuffle(multipliers.begin(), multipliers.end());
//
//        for (size_t i = 1; i != 3; ++i)
//            accumulator /= multipliers[i];
//
//        if (!(accumulator == multipliers[0])) {
//            cout << "WA" << endl;
//            for (size_t i = 0; i != 3; ++i) cout << multipliers[i] << " ";
//            cout << endl;
//            cout << accumulator << endl;
//            return 0;
//        }
//    }
//    for (int i = 100; i < 1000; ++i) {
//        for (int j = 0; j < 1000; ++j) {
//            if (j == 0) continue;
//            big_integer a(gen_random_string(i));
//            big_integer b(gen_random_string(j));
//            big_integer c = a * b;
//            if (!(c / a == b)) {
//                cout << a << " " << b << " " << c << " " << c / a << endl;
//                big_integer q = c / b;

//                return 0;
//            }
//            assert(c / b == a);
//        }
//        std::cout << i << std::endl;
//    }

//    for (int i = -100; i <= 100; ++i) {
//        for (int j = -100; j <= 100; ++j) {
//            if (j == 0) continue;
//            big_integer a = i;
//            big_integer b(j);
//            big_integer c = i & j;

//            if ((a & b) != c) {
//                cout << a << " " << b << " " << " " << (a & b) << " " << c << endl;

//                big_integer c = a & b;

//            }
//        }
//    }

//    for (int i = 0; i < 10; ++i) {
//           big_integer a = i;
//           big_integer b = -i - 1;
//           cout << (~a) << " " << b << endl;
//           if (~a != b) {
//               cout << i << " " << ~i << endl;
//               cout << ~a << "  " <<  b << endl;
//               return 0;
//           }
//    }
    return 0;
}

