#ifndef STACK_CPP
#define STACK_CPP

template<typename T>
void stack<T>::push(const T &value) {
    lst.insert(lst.begin(), value);
}

template<typename T>
T stack<T>::pop() {
    T ans = *lst.begin();
    lst.remove(lst.begin(), ++lst.begin());
    return ans;
}

#endif

