#ifndef HASH_SET_HPP
#define HASH_SET_HPP

#include "list.h"
#include "dyn_array.hpp"
#include <functional>

template<typename T>
struct hash_set {
    dyn_array<list<T>*> data;
    int cnt;

    hash_set();
    ~hash_set();

    void insert(const T &value);
    bool contains(const T &value);
    void del(const T &value);
};

#include "hash_set.cpp"

#endif

