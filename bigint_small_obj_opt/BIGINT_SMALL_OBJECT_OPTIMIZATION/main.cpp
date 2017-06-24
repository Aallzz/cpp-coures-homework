#include <bits/stdc++.h>
#include "big_integer.h"
#include <memory>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    big_integer a(10);
    big_integer b("12");
    std::cout << (a  + b) << std::endl;
    return 0;
}
