#ifndef QUEUE_CPP
#define QUEUE_CPP

template<typename T>
void queue<T>::push(T &&value) {
    lst.insert(lst.end(), value);
}

template<typename T>
T queue<T>::pop() {
    T ans = *lst.begin();
    lst.remove(lst.begin(), ++lst.begin());
    return ans;
}

#endif

