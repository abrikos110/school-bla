#ifndef HEAP_CPP
#define HEAP_CPP

template<typename T>
heap<T>::heap () {
    data.resize(16);
}

template<typename T>
void heap<T>::sift_up(int index) {
    int i = index;
    while (i > 0 && data[i] > data[(i-1)/2]) {
        std::swap(data[i], data[(i-1)/2]);
        i = (i-1)/2;
    }
}

template<typename T>
void heap<T>::sift_down(int index) {
    int i = index;
    while (2*i+1 < data.size) {
        int ix = 2*i+1;
        if (2*i+2 < data.size && data[2*i+2] > data[2*i+1])
            ix = 2*i+2;
        if (data[ix] <= data[i])
            break;
        std::swap(data[i], data[ix]);
        i = ix;
    }
}

template<typename T>
void heap<T>::insert(const T &value) {
    data.insert(value);
    sift_up(data.size - 1);
}

template<typename T>
T heap<T>::pop_max() {
    if (data.size < 2)
        return data.pop();
    T ans = data[0];
    data[0] = data.pop();
    sift_down(0);
    return ans;
}

template<typename T>
void heap<T>::insert_from(T *begin, T *end) {
    for (T *p = begin; p < end; ++p)
        data.insert(*p);
    for (int i = data.size / 2; i >= 0; --i)
        sift_down(i);
}

#endif

