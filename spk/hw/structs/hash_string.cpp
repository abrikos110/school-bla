#ifndef HASH_STRING_CPP
#define HASH_STRING_CPP

uint64_t fast_pow(uint64_t a, uint64_t b, uint64_t mod) {
    if(b == 0) return 1;
    if(b == 1) return a;
    if(b % 2 == 0) {
        uint64_t res = fast_pow(a, b / 2, mod) % mod;
        return (res * res) % mod;
    }
    else {
        return ( a * (fast_pow(a, b-1, mod) % mod) ) % mod;
    }
}

template<uint32_t base, uint32_t mod>
hash_string<base, mod>::hash_string() {}

template<uint32_t base, uint32_t mod>
template<typename iter_type>
hash_string<base, mod>::hash_string(const iter_type &begin,
                                    const iter_type &end) {
    this->update(begin, end);
}

template<uint32_t base, uint32_t mod>
template<typename container_type>
hash_string<base, mod>::hash_string(const container_type &container) {
    this->update(container.begin(), container.end());
}

template<uint32_t base, uint32_t mod>
template<typename iter_type>
void hash_string<base, mod>::update(const iter_type & begin,
                                    const iter_type & end) {
    hs.clear();
    uint32_t bp = 1;
    hs.insert(0, -1);
    for( iter_type i = begin; i != end; i++ ) {
        hs.insert(((*i * (uint64_t)bp) % mod
                   + hs[-1]) % mod, -1);
        bp = ((uint64_t)bp * base) % mod;
    }
}

template<uint32_t base, uint32_t mod>
template<typename container_type>
void hash_string<base, mod>::update(const container_type &container) {
    this->update(container.begin(), container.end());
}

template<uint32_t base, uint32_t mod>
typename hash_string<base, mod>::slice
  hash_string<base, mod>::operator[] (std::pair<idx_t, idx_t> lr) {
    auto &from = lr.first, &to = lr.second;
    if(from < 0) from += hs.size;
    if(to < 0) to += hs.size;
    return slice(this, from, to);
}

template<uint32_t base, uint32_t mod>
uint32_t hash_string<base, mod>::operator[] (idx_t i) {
    if (i < 0) i += hs.size;
    return hs[i];
}

template<uint32_t base, uint32_t mod>
size_t hash_string<base, mod>::size() {
    return hs.size - 1;
}

template<uint32_t base, uint32_t mod>
bool hash_string<base, mod>::slice::operator== (const slice &other) {
    if(to - from != other.to - other.from)
        return false;

    uint64_t myhsh = ((int64_t)(*str)[to] - (*str)[from] + mod) % mod;
    uint64_t othsh = ((int64_t)(*other.str)[other.to]
                      - (*other.str)[other.from] + mod) % mod;

    if(from < other.from)
        myhsh = (myhsh * fast_pow(base, other.from - from, mod)) % mod;
    else
        othsh = (othsh * fast_pow(base, from - other.from, mod)) % mod;
    return myhsh == othsh;
}

template<uint32_t base, uint32_t mod>
bool hash_string<base, mod>::slice::operator!= (const slice &other) {
    return !((*this) == other);
}

template<uint32_t base, uint32_t mod>
bool hash_string<base, mod>::operator== (const slice &other) {
    return ((*this)[{0, -1}]) == other;
}

template<uint32_t base, uint32_t mod>
bool hash_string<base, mod>::operator!= (const slice &other) {
    return ((*this)[{0, -1}]) != other;
}

#endif

