#ifndef TREAP_CPP
#define TREAP_CPP

template<typename T>
treap<T>::node::node(const T& x, int y, node *left, node *right)
    : x(x), y(y), left(left), right(right) {}

template<typename T>
void treap<T>::node::split(node *tree, const T& val, node *&t1, node *&t2, bool strict) {
    if (tree == nullptr)
        t1 = t2 = nullptr;
    else if (val < tree->x || (strict && val == tree->x)) {
        split(tree->left, val, t1, t2);
        tree->left = t2;
        t2 = tree;
    }
    else {
        split(tree->right, val, t1, t2);
        tree->right = t1;
        t1 = tree;
    }
}

template<typename T>
void treap<T>::node::merge(node *t1, node *t2, node *&t) {
    if (t1 == nullptr)
        t = t2;
    else if (t2 == nullptr)
        t = t1;
    else if (t2->y < t1->y) {
        merge(t1->right, t2, t1->right);
        t = t1;
    }
    else {
        merge(t1, t2->left, t2->left);
        t = t2;
    }
}

template<typename T>
int treap<T>::node::rand_y() {
    return std::rand()*(RAND_MAX+1ull) + std::rand();
}

template<typename T>
treap<T>::treap()
    : root(nullptr) {}

template<typename T>
treap<T>::~treap() {
    if (root != nullptr)
        delete root;
}

template<typename T>
treap<T>::node::~node() {
    if (right != nullptr)
        delete right;
    if (left != nullptr)
        delete left;
}

template<typename T>
bool treap<T>::contains(const T& val, node *cur) {
    if (cur == nullptr)
        cur = root;
    if (cur == nullptr)
        return false;
    if (cur->x == val)
        return true;
    else if (cur->left != nullptr && cur->x > val)
        return contains(val, cur->left);
    else if (cur->right != nullptr)
        return contains(val, cur->right);
    return false;
}

template<typename T>
void treap<T>::insert(const T& val) {
    node *t1, *t2;
    node::split(root, val, t1, t2);
    node::merge(t1, new node(val, node::rand_y()), t1);
    node::merge(t1, t2, root);
}

template<typename T>
void treap<T>::remove(const T& val) {
    if (root == nullptr)
        return;
    node *t1, *t2, *t3;
    node::split(root, val, t1, t3);
    if (t3 != nullptr) {
        t2 = t3;
        while (t2->left != nullptr)
            t2 = t2->left;
        node::split(t3, t2->x, t2, t3, true);
        if (t2 != nullptr)
            delete t2;
    }
    node::merge(t1, t3, root);
}

template<typename T>
void treap<T>::map(void (*func)(const T&), node *cur) {
    if (cur == nullptr)
        cur = root;
    if (cur == nullptr)
        return;
    if (cur->left != nullptr)
        map(func, cur->left);
    func(cur->x);
    if (cur->right != nullptr)
        map(func, cur->right);
}

#endif

