#ifndef HEAP_HPP
#define HEAP_HPP

#include "dyn_array.hpp"
#include <utility>

template<typename T>
struct heap {
    dyn_array<T> data;

    heap();

    void sift_up(int index);
    void sift_down(int index);

    void insert(const T &value);
    T pop_max();
    void insert_from(T *begin, T *end);
};

#include "heap.cpp"

#endif

