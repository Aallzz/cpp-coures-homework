#ifndef SMART_LINKED_POINTER_H
#define SMART_LINKED_POINTER_H

template<typename T>
struct smart_shared_pointer{
    int* count {};
    T* ptr {};

    smart_shared_pointer() = default;

    explicit smart_shared_pointer(T *nptr) : ptr(nptr) {
        count = new count {0};
    }



}
#endif // SMART_LINKED_POINTER_H
