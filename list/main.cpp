#include <iostream>
#include <string>
#include "list.h"

using namespace exam;

template struct list<int>;
template struct list<std::string>;

int main()
{
    list<int> c;
    c.push_back(1);
    c.pop_front(1);
    c.push_back(2);
    c.pop_front(2);
    for (int i = 0; i < 5; ++i) c.push_back(i);
    list<int> b;
    b.push_back(9);
    b.push_back(10);
    auto it = c.end();

    c.splice(--(--it), b, b.begin(), b.end());
    it--;
    c.erase(it);

//    cout << *it << endl;

    for (auto it = c.begin(); it != c.end(); ++it) {
        cout << *it << " ";
        if (it == c.end()) break;
    }

    cout << endl;

    return 0;
}
