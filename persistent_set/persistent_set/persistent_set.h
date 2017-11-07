#ifndef PERSISTENT_SET_H
#define PERSISTENT_SET_H

#include <memory>

template <typename T, template<typename> class scoped_ptr = std::shared_ptr>
struct persistent_set
{
    using value_type = T;

    struct iterator;

    persistent_set();
    persistent_set(persistent_set const&) noexcept;
    persistent_set(persistent_set&&) noexcept;

    persistent_set& operator=(persistent_set const& rhs) noexcept;
    persistent_set& operator=(persistent_set&& rhs) noexcept;

    ~persistent_set();

    iterator find(value_type) noexcept;

    std::pair<iterator, bool> insert(value_type);
    std::pair<iterator, bool> insert(value_type&&);

    void erase(iterator) noexcept;

    iterator begin() const noexcept;
    iterator end() const noexcept;

private:

    struct snode {
        scoped_ptr<snode> left {};
        scoped_ptr<snode> right {};
        scoped_ptr<snode> parent {};

        scoped_ptr<snode> get_minimum() {
            scoped_ptr<snode> cur{this};
            while (cur->left) cur = cur->left;
            return cur;
        }

        scoped_ptr<snode> get_maximum() {
            scoped_ptr<snode> cur{this};
            while (cur->right) cur = cur->right;
            return cur;
        }

        scoped_ptr<snode> next() {
            if (right)  return right->get_minimum();
            scoped_ptr<snode> up {parent};
            scoped_ptr<snode> down {this};
            while (up && down == up->right) {
                down = up;
                up = up->parent;
            }
            return up;
        }

        scoped_ptr<snode> prev() {
            if (left) return left->get_maximum();
            scoped_ptr<snode> up {parent};
            scoped_ptr<snode> down {this};
            while (up && down == up->left) {
                down = up;
                up = up->parent;
            }
            return up;
        }

    };

    struct node : snode {
        T value;

        scoped_ptr<snode> find(T const& val) {
            scoped_ptr<snode> cur{this};
            scoped_ptr<snode> from;
            while (cur && val != value) {
                from = cur;
                cur = (val <= value ? cur->left : cur->right);
            }
            if (!cur) cur = from;
            return cur;
        }

        void scoped_ptr<snode> insert(T const& val) {
            scoped_ptr<snode> cur = find(val);
            scoped_ptr<snode> new_vertex = std::static_pointer_cast<snode>(scoped_ptr<node>(val));

        }

        void erase(T const& val) {

        }
    };

    scoped_ptr<snode> root;
};

template <typename T, template<typename> class scoped_ptr>
struct persistent_set<T, scoped_ptr>::iterator
{
    value_type const& operator*() const;

    iterator& operator++();
    iterator operator++(int);

    iterator& operator--();
    iterator operator--(int);
};


template <typename T, template<typename> class scoped_ptr>
bool operator ==(typename persistent_set<T, scoped_ptr>::iterator a,
                typename persistent_set<T, scoped_ptr>::iterator b) {
    return true;
}
//bool operator!=(persistent_set::iterator, persistent_set::iterator);


#endif // PERSISTENT_SET_H
