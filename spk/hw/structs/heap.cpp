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
    int i = 0;
    while (2*i+1 < data.size) {
        int ix = 2*i+2;
        if (2*i+2 >= data.size || data[2*i+2] < data[2*i+1])
            ix = 2*i+1;
        if (data[ix] <= data[i])
            break;
        std::swap(data[i], data[ix]);
        i = ix;
    }
    return ans;
}

template<typename T>
void heap<T>::insert_from(int n, T *array) {
    for (T *p = array; p < array + n; ++p)
        data.insert(*p);
    n = data.size;
    int j = 1;
    while (j < n+1)
        j <<= 1;
    while (j > 1) {
        for (int i = std::min(j, n)-1; i > 0; --i)
            if (data[i] > data[(i-1)/2])
                std::swap(data[i], data[(i-1)/2]);
        j >>= 1;
    }
}

#endif

