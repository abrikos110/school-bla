#ifndef LIST_CPP
#define LIST_CPP

template<typename T>
list<T>::node::node(const T &data, node *next)
    : data(data), next(next) {}

template<typename T>
list<T>::iterator::iterator(node *prev, node *cur)
    : prev(prev), cur(cur) {}

template<typename T>
T& list<T>::iterator::operator* () {
    return cur->data;
}

template<typename T>
typename list<T>::iterator& list<T>::iterator::operator++ () {
    prev = cur;
    cur = cur->next;
    return *this;
}

template<typename T>
typename list<T>::iterator list<T>::iterator::operator++ (int) {
    list<T>::iterator copy = *this;
    ++(*this);
    return copy;
}

template<typename T>
bool list<T>::iterator::operator== (list<T>::iterator it) {
    return prev == it.prev && cur == it.cur;
}

template<typename T>
bool list<T>::iterator::operator!= (list<T>::iterator it) {
    return prev != it.prev || cur != it.cur;
}

template<typename T>
list<T>::list()
    : head(nullptr), tail(nullptr) {}

template<typename T>
typename list<T>::iterator list<T>::begin() {
    return list<T>::iterator(nullptr, head);
}

template<typename T>
typename list<T>::iterator list<T>::end() {
    return list<T>::iterator(tail, nullptr);
}

template<typename T>
list<T> list<T>::slice(list<T>::iterator from, list<T>::iterator to) {
    list ans;
    ans.head = from.cur;
    ans.tail = to.prev;
    ans.tail->next = nullptr;
    if (from.prev != nullptr)
        from.prev->next = to.cur;
    else
        head = to.cur;
    return ans;
}

template<typename T>
void list<T>::insert(list<T>::iterator before, const T &value) {
    list<T>::node *ins = new list<T>::node(value, before.cur);
    if (before.prev != nullptr)
        before.prev->next = ins;
    else
        head = ins;
    if (before.cur == nullptr)
        tail = ins;
}

template<typename T>
void list<T>::insert(list<T>::iterator before, const list<T> &values) {
    if (before.prev != nullptr)
        before.prev->next = values.head;
    else
        head = values.head;
    if (before.cur == nullptr)
        tail = values.tail;
    values.head = values.tail = nullptr;
}

template<typename T>
list<T>::~list() {
    if (head == nullptr)
        return;
    node *cur = head;
    while (cur != nullptr) {
        node *next = cur->next;
        delete cur;
        cur = next;
    }
}

template<typename T>
void list<T>::remove(list<T>::iterator from, list<T>::iterator to) {
    auto lst = this->slice(from, to);
    lst.~list();
    lst.head = lst.tail = nullptr;
}

template<typename T>
list<T>::list(const list<T> &lst) {
    node *cur = lst.head;
    while (cur != nullptr) {
        node *next = cur->next;
        insert(end(), cur->data);
        cur = next;
    }
}

template<typename T>
typename list<T>::iterator list<T>::find(const T &value) {
    list<T>::iterator it = this->begin();
    for (; it != this->end(); ++it)
        if (*it == value)
            break;
    return it;
}

#endif

