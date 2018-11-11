#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

template<typename T>
struct stack {
    list<T> lst;

    void push(const T &value);
    T pop();
};

#include "stack.cpp"

#endif

