#ifndef DEQUE

#define DEQUE

#include <type_traits>
#include <iterator>
#include <cstddef>
#include <cassert>

template<typename T>
struct deque {

    template<typename V>
    struct deque_iterator {

        T *cur;
        T *p;
        size_t cap;
        size_t id;
        size_t sz;
        size_t start;

        deque_iterator(T *cur, T* p, size_t cap, size_t id, size_t sz, size_t start)
            : cur(cur),
              p(p),
              cap(cap),
              id(id),
              sz(sz),
              start(start)
        {}

        deque_iterator(deque_iterator const& other)
            : cur(other.cur),
              p(other.p),
              cap(other.cap),
              id(other.id),
              sz(other.sz),
              start(other.start)
        {}

        template <typename U>
        deque_iterator(const deque_iterator<U> &data,
            typename std::enable_if<std::is_same<V, const U>::value>::type* = nullptr)
            : cur(data.cur)
        {}

        deque_iterator& operator +=(int a) {
            (id += a) %= cap;
            cur = p + id;
            return *this;
        }

        friend deque_iterator operator +(int c, deque_iterator const& p) {
            deque_iterator k(p);
            return k += c;
        }

        deque_iterator& operator +(int c) const{
            deque_iterator k(*this);
            return k += c;
        }

        deque_iterator& operator -=(int a) {
            (id += cap - a) %= cap;
            cur = p + id;
            return *this;
        }

        deque_iterator& operator -(int c) const{
            deque_iterator k(*this);
            return k -= c;
        }

        ptrdiff_t operator -(deque_iterator const& q) const{
            if (start + sz <= cap) {
                return id - q.id;
            } else {
                return (id - start) + (cap - q.id);
            }
        }

        deque_iterator& operator++() {
            cur++;
            id++;
            if (cur == p + cap)
                cur = p, id = 0;
            return *this;
        }

        ptrdiff_t operator +(deque_iterator const& q) const {
            return q.id - this->id;
        }

        bool operator < (deque_iterator const& q) const {
            if (start + sz <= cap) {
                return id < q.id;
            } else {
                return id > q.id;
            }
        }

        bool operator == (deque_iterator<T>& q) const {
            return (q.cap == cap && q.cur == cur && q.id == id && q.p == p && q.sz == sz && q.start == start);
        }

        bool operator == (deque_iterator<const T>& q) const {
            return (q.cap == cap && q.cur == cur && q.id == id && q.p == p && q.sz == sz && q.start == start);
        }

        bool operator > (deque_iterator<T> const& q) const {
            return q < *this;
        }

        bool operator > (deque_iterator<const T> const& q) const {
            return q < *this;
        }

        bool operator <= (deque_iterator<T> const& q) const {
            return !(*this > q);
        }

        bool operator <= (deque_iterator<const T> const& q) const {
            return !(*this > q);
        }

        bool operator >= (deque_iterator<T> const& q) const {
            return !(*this < q);
        }

        bool operator >= (deque_iterator<const T> const& q) const {
            return !(*this < q);
        }

        deque_iterator& operator--() {
            if (cur == p) {
                cur = cur + cap - 1;
                id = cap - 1;
            } else {
                cur--;
                id--;
            }
            return *this;
        }

        deque_iterator operator++(int) {
            deque_iterator was(*this);
            ++(*this);
            return was;
        }

        deque_iterator operator--(int) {
            deque_iterator was(*this);
            --(*this);
            return was;
        }

        V & operator*() const {
            return *cur;
        }


        friend bool operator!=(deque_iterator a, deque_iterator b) {
            return a.cur != b.cur;
        }

        typedef std::ptrdiff_t difference_type;
        typedef V value_type;
        typedef V* pointer;
        typedef V& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

    };

    typedef deque_iterator<T> iterator;
    typedef deque_iterator<const T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    deque();
    deque(deque const& other);

    ~deque();

    deque& operator =(deque const& other);
    T& operator [](size_t pos);
    T const& operator[](size_t pos) const;

    bool empty() const;
    size_t size() const;

    void clear();

    void push_back(T const& element);
    void push_front(T const& element);
    void pop_back();
    void pop_front();

    T const& front() const;
    T& front();
    T const& back() const;
    T& back();

    iterator insert(const iterator pos, T const& element);
    iterator erase(const iterator pos);

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

    template <typename TT>
    friend void swap(deque<TT>& a, deque<TT>& b);
private:
    T *p{nullptr};
    size_t start{0};
    size_t sz{0};
    size_t capacity{0};

    void ensure_capacity(int new_capacity);
    void push_back_realloc(T const& element);
    void push_front_realloc(T const& element);

};

template<typename T>
void initialize_data(T* distance, T* source, size_t sz);

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
    if (!p) return  iterator(p, p, capacity, start, sz, start);
    return iterator(p + start, p, capacity, start, sz, start);
}

template<typename T>
typename deque<T>::const_iterator deque<T>::begin() const {
    if (!p) return const_iterator(p, p, capacity, start, sz, start);
    return const_iterator(p + start, p, capacity, start, sz, start);
}

template<typename T>
typename deque<T>::iterator deque<T>::end() {
    if (!p) return iterator(p, p, capacity, start + sz, sz, start);
    return iterator(p + (start + sz) % capacity, p, capacity, (start + sz) % capacity, sz, start);
}

template<typename T>
typename deque<T>::const_iterator deque<T>::end() const {
    if (!p) return const_iterator(p, p, capacity, start + sz, sz, start);
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
        iit--;
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



#endif // DEQUE
