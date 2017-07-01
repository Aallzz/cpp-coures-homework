#ifndef DEQUE

#define DEQUE

#include <type_traits>
#include <iterator>
#include <cstddef>

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

        bool operator == (deque_iterator const& q) const {
            return (q.cap == cap && q.cur == cur && q.id == id && q.p == p && q.sz == sz && q.start == start);
        }

        bool operator > (deque_iterator const& q) const {
            return q < *this;
        }

        bool operator <= (deque_iterator const& q) const {
            return !(*this > q);
        }

        bool operator >= (deque_iterator const& q) const {
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


#endif // DEQUE
