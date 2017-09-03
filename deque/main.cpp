#include <iostream>
#include <string>
#include "list.h"

using namespace exam;

template struct list<int>;
template struct list<std::string>;
template struct list<list<int>>;

using std::cout;
using std::endl;

list<int> f(int start, int finish) {
    list<int> res;
    while (start != finish) {
        res.push_back(start);
        start++;
    }
    return res;
}

int main()
{
    list<int> c;
    c.push_back(1);
    c.pop_front();
    c.push_back(2);
    c.pop_front();
    for (int i = 0; i < 5; ++i) c.push_back(i);
    list<int> b;
    b.push_back(9);
    b.push_back(10);
    auto it = c.end();
    auto iit = b.end();
    c.splice(--(--it), b, b.begin(), --iit);
    --(--it);
    auto pit = it;
    it = c.erase(it);
    it = c.erase(c.erase(it));
    cout << *it << endl;
    c.insert(it, 11);
//    c.clear();
    list<int> d;
    d = c;
    b.push_front(12);
    b.pop_back();
//    b.pop_back();
//    b.pop_front();
//    cout << *it << endl;
    d.splice(d.begin(), b, b.begin(), b.end());
//    d.splice(c.begin(), b, b.begin(), b.end());
    std::cout << "OK" << std::endl;
    for (auto iit = d.rbegin(); iit != d.rend(); ++iit) {
        cout << *iit << " ";
    }
    cout << endl;
    for (auto it = b.begin(); it != b.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    cout << *it << endl;

    c = f(20, 40);
    for (auto i : c) {
        cout << i << " ";
    }
    cout << endl;

    list<int> l {1, 2, 3};
    return 0;
}
