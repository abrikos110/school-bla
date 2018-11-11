#ifndef HEAP_CPP
#define HEAP_CPP

template<typename T>
heap<T>::heap () {
    data.resize(16);
}

template<typename T>
void heap<T>::sift_up(int index) {
    int i = index;
    while (i > 0 || data[i] > data[(i-1)/2]) {
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
    while (2*i+1 >= data.size)
        if (2*i+2 < data.size && data[2*i+2] > data[2*i+1]) {
            std::swap(data[i], data[2*i+2]);
            i = 2*i+2;
        }
        else if (2*i+1 < data.size) {
            std::swap(data[i], data[2*i+1]);
            i = 2*i+1;
        }
}

#endif

