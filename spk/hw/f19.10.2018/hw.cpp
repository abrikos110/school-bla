#ifndef SPK_TEMPLATES_H
#define SPK_TEMPLATES_H

template<typename T>
class list {
    class node;
  
public:
    class iter {
        node *elem;
    
      public:
        iter(node *elem);

        bool operator== (iter &&i);
        bool operator!= (iter &&i);

        iter& operator++ ();

        T& operator* ();
    };

private:
    class node {
        friend list;
        friend iter;
        T data;
        node *next;
    public:
        node(T &&x, node *next = nullptr);
        ~node();
    };

    node *head;

public:
    list();
    ~list();

    iter begin();
    iter end();

    iter insert(iter i);
};

#endif


#ifndef SPK_TEMPLATES_CPP
#define SPK_TEMPLATES_CPP

template<>

#endif

#include <iostream>


int main() {
    return 0;
}

