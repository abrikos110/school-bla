#ifndef DYN_ARRAY_CPP
#define DYN_ARRAY_CPP

template<typename T>
dyn_array<T>::dyn_array(int reserved)
    : size(0), reserved(reserved) {
    data = new T[reserved];
}

template<typename T>
dyn_array<T>::~dyn_array() {
    delete [] data;
}

template<typename T>
void dyn_array<T>::resize(int reserved) {
    T *new_data = new T[reserved];
    for (int i = 0; i < std::min(size, reserved); ++i)
        new_data[i] = data[i];
    delete [] data;
    data = new_data;
    this->reserved = reserved;
}

template<typename T>
void dyn_array<T>::clear() {
    delete [] data;
    data = new T[reserved = 16];
    size = 0;
}

template<typename T>
void dyn_array<T>::insert(const T &value, int index) {
    if (index < 0)
        index += size + 1;
    if (size == reserved)
        resize(reserved * 2);

    int i = size++;
    data[i] = value;
    while (i != index) {
        std::swap(data[i], data[i-1]);
        --i;
    }
}

template<typename T>
T dyn_array<T>::pop(int index) {
    if (index < 0)
        index += size;
    int i = index;
    --size;
    while (i < size) {
        std::swap(data[i], data[i+1]);
        ++i;
    }

    return data[size];
}

template<typename T>
T& dyn_array<T>::operator [] (int index) {
    if (index < 0)
        index += size;
    return data[index];
}

#endif

