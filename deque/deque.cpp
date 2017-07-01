#include "deque.h"

#include <iostream>
#include <cassert>

template<typename T>
deque<T>::deque() {}

template<typename T>
deque<T>::deque(deque const& other)
{
    ensure_capacity(other.capacity);
    if (other.start + other.sz <= other.capacity) {
        initialize_data(p, other.p + other.start, other.sz);
    } else {
        initialize_data(p, other.p + other.start, other.capacity - other.start);
        initialize_data(p + other.capacity - other.start, other.p, other.sz - (other.capacity - other.start));
    }
    sz = other.sz;
}

template<typename T>
deque<T>::~deque() {
//    if (std::is_trivially_destructible<T>::value) {
//        return ;
//    }
    while (sz) {
        p[start].~T();
        (start += 1) %= capacity;
        sz--;
    }

    delete p;
}

template<typename T>
deque<T>& deque<T>::operator =(deque const& other) {
    deque temp(other);
    swap(*this, temp);
    return *this;
}

template<typename T>
T& deque<T>::operator [](size_t pos) {
    return p[(start + pos) % capacity];
}

template<typename T>
T const& deque<T>::operator [](size_t pos) const {
    return (p + (start + pos) % capacity);
}

template<typename T>
bool deque<T>::empty() const {
    return (sz == 0);
}

template<typename T>
size_t deque<T>::size() const {
    return sz;
}

template<typename T>
void deque<T>::clear() {
    if (start + sz <= capacity)
        clear_data(p + start, sz);
    else {
        clear_data(p + start, capacity - sz);
        clear_data(p, sz - (capacity - sz));
    }
}

template<typename T>
void deque<T>::push_back(T const& element) {
    if (sz != capacity && sz != capacity - 1) {
        new (p + (start + sz) % capacity) T(element);
        // std::cerr << element << " " << *(p + (start + sz) % capacity) << std::endl;
        sz++;
    } else {
        push_back_realloc(element);   // выделение новой памяти + push_back
    }
}

template<typename T>
void deque<T>::push_front(T const& element) {
    if (sz != capacity && sz != capacity - 1) {
        sz++;
        if (start == 0)
            start = capacity - 1;
        else
            start--;
        new (p + start) T(element);
    } else {
        push_front_realloc(element);
    }
}


template <typename T>
void deque<T>::push_back_realloc(T const& element)
{
    deque<T> temp;
    size_t new_capacity = (capacity == 0 ? 4 : (3 * capacity) / 2);
    temp.ensure_capacity(new_capacity); // выделили помять для placement new
    if (start + sz <= capacity) {
        initialize_data(temp.p, p + start, sz);
    } else {
        initialize_data(temp.p, p + start, capacity - start);
        initialize_data(temp.p + capacity - start, p, sz - (capacity - start));
    }

    temp.start = 0;
    temp.sz = sz;
    temp.capacity = new_capacity;

    temp.push_back(element);

    swap(*this, temp);

    assert(sz <= capacity);
}

template<typename T>
void deque<T>::push_front_realloc(const T &element) {
    deque<T> temp;
    size_t new_capacity = (capacity == 0 ? 4 : (3 * capacity) / 2);
    temp.ensure_capacity(new_capacity);
    if (start + sz <= capacity) {
        initialize_data(temp.p, p + start, sz);
    } else {
        initialize_data(temp.p, p + start, capacity - start);
        initialize_data(temp.p + capacity - start, p, sz - (capacity - start));
    }

    temp.start = 0;
    temp.sz = sz;
    temp.capacity = new_capacity;

    temp.push_front(element);
    swap(*this, temp);
}

template<typename T>
void deque<T>::pop_back() {
    if (sz == 0) return ;
    int pos = (start + sz - 1) % capacity;
    p[pos].~T();
    sz--;
}

template<typename T>
void deque<T>::pop_front() {
    if (sz == 0) return ;
    p[start].~T();
    sz--;
    (start += 1) %= capacity;
}

template<typename T>
T const& deque<T>::front() const {
    return p[start];
}

template<typename T>
T& deque<T>::front() {
    return p[start];
}

template<typename T>
T const& deque<T>::back() const {
    return p[(start + sz - 1) % capacity];
}

template<typename T>
T& deque<T>::back() {
    return p[(start + sz - 1) % capacity];
}

template<typename T>
void deque<T>::ensure_capacity(int new_capacity) {

    if (new_capacity <= capacity) return ;

    deque temp;

    if (new_capacity != 0) {
        temp.p = static_cast<T*>(operator new(new_capacity * sizeof(T)));
//        if (start + sz <= capacity) {
//            initialize_data(temp.p, p + start, sz);
//        } else {
//            initialize_data(temp.p, p + start, capacity - start);
//            initialize_data(temp.p + capacity - start, p, sz - (capacity - start));
//        }
        temp.capacity = new_capacity;
        temp.start = 0;
        temp.sz = sz;
    }

    swap(*this, temp);
}

template<typename T>
void initialize_data(T* distance, T* source, size_t sz) {
    for (size_t i = 0; i < sz; ++i) {
        new (distance + i) T(source[i]);
    }
}

template<typename T>
void swap(deque<T>& a, deque<T>& b) {
    std::swap(a.p, b.p);
    std::swap(a.start, b.start);
    std::swap(a.sz, b.sz);
    std::swap(a.capacity, b.capacity);
}

template<typename T>
void clear_data(T* data, size_t sz,typename std::enable_if<!std::is_trivially_destructible<T>::value>::type* = nullptr) {
    for (size_t i = sz; i != 0; --i) {
        data[i - 1].~T();
    }
}

template<typename T>
void clear_data(T* data, size_t sz, typename std::enable_if<std::is_trivially_destructible<T>::value>::type* = nullptr)
{}

template<typename T>
typename deque<T>::iterator deque<T>::begin() {
    return iterator(p + start, p, capacity, start, sz, start);
}

template<typename T>
typename deque<T>::const_iterator deque<T>::begin() const {
    return const_iterator(p + start, p, capacity, start, sz, start);
}

template<typename T>
typename deque<T>::iterator deque<T>::end() {
    return iterator(p + (start + sz) % capacity, p, capacity, (start + sz) % capacity, sz, start);
}

template<typename T>
typename deque<T>::const_iterator deque<T>::end() const {
    return const_iterator(p + (start + sz) % capacity, p, capacity, (start + sz) % capacity, sz, start);
}

template<typename T>
typename deque<T>::reverse_iterator deque<T>::rbegin() {
    return reverse_iterator(end());
}

template<typename T>
typename deque<T>::const_reverse_iterator deque<T>::rbegin() const {
    return const_reverse_iterator(end());
}

template<typename T>
typename deque<T>::reverse_iterator deque<T>::rend() {
    return reverse_iterator(begin());
}

template<typename T>
typename deque<T>::const_reverse_iterator deque<T>::rend() const {
    return const_reverse_iterator(begin());
}

template<typename T>
typename deque<T>::iterator deque<T>::insert(const iterator it, const T& element) {

    ptrdiff_t dist1 = it - begin();
    ptrdiff_t dist2 = end() - it;
    size_t pos = it.id;
    T temp = element;
    iterator iit(it);
    if (dist1 >= dist2) {
        while (iit + 1 != begin() && iit != end()) {
            std::swap(*iit, temp);
            iit--;
        }
        push_front(temp);
    } else {
        while (iit != end()) {
            std::swap(*iit, temp);
            iit++;
        }
        push_back(temp);
    }
    return iterator(p + pos, p, capacity, pos, sz, start);
}

template<typename T>
typename deque<T>::iterator deque<T>::erase(const iterator it) {
    ptrdiff_t dist1 = it - begin();
    ptrdiff_t dist2 = end() - it;
    iterator iit(it);
    if (dist1 > dist2) {
        size_t pos = it.id + 1;
        if (iit > begin()) {
            while (iit != begin()) {
                std::swap(*iit, *(iit - 1));
                iit--;
            }
        }
        clear_data(p + iit.id, 1);
        sz--;
        start++;
        start %= capacity;
        pos %= capacity;
        return iterator(p + pos, p, capacity, pos, sz, start);
    } else {
        size_t pos = it.id;
        if (iit < end()) {
            while (iit + 1 != end()) {
                std::swap(*iit, *(iit + 1));
                iit++;
            }
        }
        clear_data(p + iit.id, 1);
        sz--;
        return iterator(p + pos, p, capacity, pos, sz, start);
    }
}

