#ifndef HASH_SET_CPP
#define HASH_SET_CPP

template<typename T>
hash_set<T>::hash_set()
    : cnt(0) {
    for (int i = 0; i < 16; ++i)
        data.insert(nullptr);
}

template<typename T>
hash_set<T>::~hash_set() {
    for (int i = 0; i < data.size; ++i)
        if (data[i] != nullptr)
            delete data[i];
}

/*template<typename T>
void hash_set<T>::insert(const T &value) {
    size_t hs = std::hash(value);

}*/

#endif

