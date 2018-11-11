#ifndef SORTED_ARRAY_HPP
#define SORTED_ARRAY_HPP

template<typename T>
struct sorted_array {
    T* data;
    int size, reserved;

    sorted_array(int reserved = 16);
    ~sorted_array();

    void resize(int reserved);
    void insert(const T &value);
    void remove(int index);
    const T& operator[] (int index);
    int lower_bound(const T &value);
    int upper_bound(const T &value);
};

#include "sorted_array.cpp"

#endif

