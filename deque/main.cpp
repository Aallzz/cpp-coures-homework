#include <iostream>
#include "deque.h"
#include "deque.cpp"

using namespace std;

deque<int> d;

void check(deque<int> d) {
    for (int i = 0; i < d.size(); ++i) {
        cout << d[i] <<  " ";
    }
    cout << endl;
}

int main()
{
    for (int i = 0; i < 10; ++i) {
        d.push_back(i);
        check(d);
    }

    for (int i = 10; i < 20; ++i) {
         d.push_front(i);
         check(d);
    }

    deque<int> b;

    deque<int>::iterator it = d.begin();
    while (it < d.end()) {
        for (deque<int>::iterator iit = d.begin(); iit != d.end(); ++iit) {
            cout << *iit << " ";
        }
        cout << endl;
        it = d.erase(it);
    }

    d.insert(d.begin(), 1);
    check(d);
    for (int i = 10; i < 20; ++i) {
        d.insert(d.begin() + 1, i);
        check(d);
    }

    for (int i = 0; i < 50; ++i) {
        if (i % 2 == 0) d.pop_front();
        else d.pop_back();
    }

    deque<int> q;
    for (int i = 0; i < 20; ++i)
    q.push_back(i);
    for (deque<int>::iterator it = q.begin(); it != q.end(); ++it)
    cout << *it << ' ';
    cout << '\n';
    for (deque<int>::reverse_iterator it = q.rbegin(); it != q.rend(); ++it)
    cout << *it << ' ';

    q.insert(q.begin() + 3, 100000);
    q.insert(q.begin() + 17, 99999);

    cout << '\n' << '\n';
    for (deque<int>::iterator it = q.begin(); it != q.end(); ++it)
    cout << *it << ' ';
    cout << '\n';
    for (deque<int>::reverse_iterator it = q.rbegin(); it != q.rend(); ++it)
    cout << *it << ' ';
    q.erase(q.begin());
    q.erase(q.begin() + 10);
    q.erase(q.begin() + 15);
    cout << '\n' << '\n';
    for (deque<int>::iterator it = q.begin(); it != q.end(); ++it)
    cout << *it << ' ';
    cout << '\n';
    for (deque<int>::reverse_iterator it = q.rbegin(); it != q.rend(); ++it)
    cout << *it << ' ';

    return 0;
}

