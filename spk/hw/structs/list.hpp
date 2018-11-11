#ifndef LIST_HPP
#define LIST_HPP

template<typename T>
struct list {
    struct node {
        T data;
        node *next;

        node(const T &data, node *next = nullptr);
    };

    struct iterator {
        node *prev, *cur;

        iterator(node *prev = nullptr, node *cur = nullptr);
        T& operator* ();
        iterator& operator++ ();
        iterator operator++ (int);
        bool operator== (iterator it);
        bool operator!= (iterator it);
    };

    node *head, *tail;

    list();
    list(const list &lst);
    ~list();

    iterator begin();
    iterator end();

    list slice(iterator from, iterator to);
    void insert(iterator before, const T &value);
    void insert(iterator before, const list<T> &values);
    void remove(iterator from, iterator to);

    iterator find(const T &value);
};

#include "list.cpp"

#endif

