#ifndef HASH_STRING_HPP
#define HASH_STRING_HPP

#include "dyn_array.hpp"

typedef ptrdiff_t idx_t;

uint64_t fast_pow(uint64_t a, uint64_t b, uint64_t mod);

template<uint32_t base = 127, uint32_t mod = 1'000'000'007>
class hash_string {
    dyn_array<uint32_t> hs;
public:
    class slice {
        hash_string<base, mod> *str;
        idx_t from, to;
    public:
        slice(hash_string<base, mod> *str, idx_t from, idx_t to)
            : str(str), from(from), to(to) {};

        bool operator== (const slice &other);
        bool operator!= (const slice &other);
    };

    hash_string();

    template<typename iter_type>
    hash_string(const iter_type &begin, const iter_type &end);

    template<typename iter_type>
    void update(const iter_type &begin, const iter_type &end);

    template<typename container_type>
    hash_string(const container_type &container);

    template<typename container_type>
    void update(const container_type &container);

    /// Usage: hstr[{from, to}]
    /// returns slice from 'from' index to 'to' without last element
    /// Example: hstr[{0, hstr.size()}] returns slice with full string
    slice operator[] (std::pair<idx_t, idx_t> lr);
    uint32_t operator[] (idx_t i);

    size_t size();
    bool operator== (const slice &other);
    bool operator!= (const slice &other);

    friend bool slice::operator== (const slice &other);
};

#include "hash_string.cpp"

#endif

