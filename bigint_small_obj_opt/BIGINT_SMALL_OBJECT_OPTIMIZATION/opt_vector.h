#ifndef OPT_VECTOR
#define OPT_VECTOR

#include <vector>
#include <cstdint>
#include <memory>

struct opt_vector {

    opt_vector();
    opt_vector(size_t sz);
    opt_vector(opt_vector const& other);

    ~opt_vector();
    size_t size() const;
    void resize(size_t new_size);

    uint32_t& operator [](size_t pos);
    uint32_t const& operator [](size_t pos) const;
    opt_vector& operator =(opt_vector const& other);

    uint32_t& back();

    void push_back(uint32_t const& a);
    void pop_back();

private:

    union {
        uint32_t number;
        std::shared_ptr<std::vector<uint32_t>> long_number;
    };

    bool is_small;
    bool is_empty;

    void update();
};

#endif // OPT_VECTOR
