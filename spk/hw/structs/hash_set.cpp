#ifndef HASH_SET_CPP
#define HASH_SET_CPP

template<typename T>
hash_set<T>::hash_set()
    : cnt(0) {
    data.size = data.reserved;
}

template<typename T>
void hash_set<T>::insert(const T &value) {
    size_t hs = std::hash(value);
    ++cnt;
    auto &lst = data[hs % data.size];
    lst.insert(lst.end(), {hs, value});

    if (cnt > data.size)
        resize();
}

template<typename T>
void hash_set<T>::resize() {
    dyn_array<list<std::pair<size_t, T>>> newdata(2*data.size);
    for (auto &l : data)
        for (auto &pr : l) {
            auto &lst = newdata[pr.first % newdata.size()];
            lst.insert(lst.end(), pr);
        }
}

#endif

