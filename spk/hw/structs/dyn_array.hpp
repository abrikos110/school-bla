#ifndef DYN_ARRAY_HPP
#define DYN_ARRAY_HPP

#include <utility>
#include <algorithm>

template<typename T>
struct dyn_array {
    T *data;
    int size, reserved;

    dyn_array(int reserved = 16);
    ~dyn_array();

    void resize(int reserved);
    void clear();
    void insert(const T &value, int index = -1);
    T pop(int index = -1);
    T& operator [] (int index);
};

#include "dyn_array.cpp"

#endif

