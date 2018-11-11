#ifndef TREAP_HPP
#define TREAP_HPP

#include <cstdlib>

template<typename T>
struct treap {
    struct node {
        T x;
        int y;
        node *left, *right;

        node(const T &x, int y,
             node *left = nullptr,
             node *right = nullptr);

        ~node();

        static int rand_y();
        static void split(node *tree, const T &val, node *&t1, node *&t2, bool strict = false);
        static void merge(node *t1, node *t2, node *&t);
    };

    /*struct iterator {
        vector<node*> path;

        iterator();
        T& operator* ();
        iterator& operator++ ();
        iterator operator++ (int);
        bool operator== (iterator &&it);
        bool operator!= (iterator &&it);
    };*/

    node *root;

    treap();
    ~treap();

    //iterator begin();
    //iterator end();

    //iterator lower_bound(T &&val);
    //iterator upper_bound(T &&val);
    bool contains(const T &val, node *cur = nullptr);
    void insert(const T &val);
    void remove(const T &val);
    void map(void (*func)(const T&), node *cur = nullptr);
};

#include "treap.cpp"

#endif

