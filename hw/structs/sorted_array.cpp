#ifndef SORTED_ARRAY_CPP
#define SORTED_ARRAY_CPP

template<typename T>
sorted_array<T>::sorted_array(int reserved) {
    size = 0;
    this->reserved = reserved;
    data = new T[reserved];
}

template<typename T>
sorted_array<T>::~sorted_array() {
    delete[] data;
}

template<typename T>
void sorted_array<T>::resize(int reserved) {
    T *new_data = new T[reserved];
    for (int i = 0; i < size; ++i)
        new_data[i] = data[i];
    delete[] data;
    data = new_data;
    this->reserved = reserved;
}

template<typename T>
void sorted_array<T>::insert(const T &value) {
    if (size == reserved) {
        resize(reserved * 2);
    }
    int i = size++;
    data[i] = value;
    for (; i != 0 && data[i] > data[i-1]; --i) {
        T tmp = data[i];
        data[i] = data[i-1];
        data[i-1] = tmp;
    }
}

template<typename T>
void sorted_array<T>::remove(int index) {
    --size;
    for (int i = index; i < size; ++i)
        data[i] = data[i+1];
}

template<typename T>
const T& sorted_array<T>::operator[] (int index) {
    return data[index];
}

template<typename T>
int sorted_array<T>::upper_bound(const T &value) {
    int l = -1, r = size-1;
    while (r-l > 1) {
        int q = (l+r) / 2;
        if (data[q] > value)
            r = q;
        else
            l = q;
    }
    return r;
}

template<typename T>
int sorted_array<T>::lower_bound(const T &value) {
    int l = -1, r = size-1;
    while (r-l > 1) {
        int q = (l+r) / 2;
        if (data[q] >= value)
            r = q;
        else
            l = q;
    }
    return r;

}

#endif

