#ifndef QUEUE_HPP
#define QUEUE_HPP

template<typename T>
struct queue {
    list<T> lst;

    void push(T &&value);
    T pop();
};

#include "queue.cpp"

#endif

