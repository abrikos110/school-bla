#ifndef HASH_SET_HPP
#define HASH_SET_HPP

#include "list.h"
#include "dyn_array.hpp"
#include <functional>
#include <utility>

template<typename T>
struct hash_set {
    dyn_array<list<std::pair<size_t, T>>> data;
    int cnt;

    hash_set();

    void insert(const T &value);
    bool contains(const T &value);
    void del(const T &value);
    void resize();
};

#include "hash_set.cpp"

#endif

