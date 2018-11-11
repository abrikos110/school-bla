#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef HASHSTRING_H
#define HASHSTRING_H

namespace PolynomialHashString
{

typedef ptrdiff_t idx_t;

uint64_t fast_pow(uint64_t a, uint64_t b, uint64_t mod)
{
    if(b == 0) return 1;
    if(b == 1) return a;
    if(b % 2 == 0) {
        uint64_t res = fast_pow(a, b / 2, mod) % mod;
        return (res * res) % mod;
    }
    else {
        return ( a * ( fast_pow(a, b-1, mod) % mod ) ) % mod;
    }
}

template<uint32_t base = 127, uint32_t mod = 1000*1000*1000 + 7> class HashString;
template<uint32_t base = 127, uint32_t mod = 1000*1000*1000 + 7> class HashStringSlice;

template<uint32_t base, uint32_t mod>
class HashString
{
    vector<uint32_t> hs;
public:
    template<typename iter_type> HashString(const iter_type & begin, const iter_type & end);
    template<typename iter_type> void update(const iter_type & begin, const iter_type & end);
    
    template<typename container_type> HashString(const container_type & container);
    template<typename container_type> void update(const container_type & container);
    
    /// Usage: hstr[{from, to}]
    /// returns slice from 'from' index to 'to' without last element
    /// Example: hstr[{0, hstr.size()}] returns slice with full string
    HashStringSlice<base, mod> slice(idx_t from, idx_t to);
    HashStringSlice<base, mod> operator[] (std::pair<idx_t, idx_t> lr);
    
    size_t size();
    bool operator== (const HashStringSlice<base, mod> & other);
    bool operator!= (const HashStringSlice<base, mod> & other);
    
    friend bool HashStringSlice<base, mod>::operator== (const HashStringSlice<base, mod> & other);
};

template<uint32_t base, uint32_t mod>
class HashStringSlice
{
    HashString<base, mod> * str;
    idx_t from, to;
public:
    HashStringSlice(HashString<base, mod> * str, idx_t from, idx_t to) : str(str), from(from), to(to) {};
    
    bool operator== (const HashStringSlice & other);
    bool operator!= (const HashStringSlice & other);
};

}

#endif


#ifndef HASHSTRING_CPP
#define HASHSTRING_CPP

namespace PolynomialHashString
{

template<uint32_t base, uint32_t mod>
template<typename iter_type>
HashString<base, mod>::HashString(const iter_type & begin, const iter_type & end)
{
    this->update(begin, end);
}

template<uint32_t base, uint32_t mod>
template<typename container_type>
HashString<base, mod>::HashString(const container_type & container)
{
    this->update(container.begin(), container.end());
}

template<uint32_t base, uint32_t mod>
template<typename iter_type>
void HashString<base, mod>::update(const iter_type & begin, const iter_type & end)
{
    hs.clear();
    uint32_t bp = 1;
    hs.push_back(0);
    for( iter_type i = begin; i != end; i++ )
    {
        hs.push_back( ( ((*i) * uint64_t(bp)) % mod + hs.back() ) % mod );
        bp = (uint64_t(bp) * base) % mod;
    }
}

template<uint32_t base, uint32_t mod>
template<typename container_type>
void HashString<base, mod>::update(const container_type & container)
{
    *this->update(container.begin(), container.end());
}

template<uint32_t base, uint32_t mod>
HashStringSlice<base, mod> HashString<base, mod>::slice(idx_t from, idx_t to)
{
    if(from < 0) from += hs.size();
    if(to < 0) to += hs.size();
    return HashStringSlice<base, mod>(this, from, to);
}

template<uint32_t base, uint32_t mod>
HashStringSlice<base, mod> HashString<base, mod>::operator[] (std::pair<idx_t, idx_t> lr)
{
    return this->slice(lr.first, lr.second);
}

template<uint32_t base, uint32_t mod>
size_t HashString<base, mod>::size()
{
    return hs.size() - 1;
}

template<uint32_t base, uint32_t mod>
bool HashStringSlice<base, mod>::operator== (const HashStringSlice & other)
{
    if(to - from != other.to - other.from)
        return false;
    
    uint64_t myhsh = (uint64_t(str->hs[to]) - str->hs[from] + mod) % mod;
    uint64_t othsh = (uint64_t(other.str->hs[other.to]) - other.str->hs[other.from] + mod) % mod;
    
    if(from < other.from)
        myhsh = ( myhsh * fast_pow(base, other.from - from, mod) ) % mod;
    else
        othsh = ( othsh * fast_pow(base, from - other.from, mod) ) % mod;
    return myhsh == othsh;
}

template<uint32_t base, uint32_t mod>
bool HashStringSlice<base, mod>::operator!= (const HashStringSlice & other)
{
    return !((*this) == other);
}

template<uint32_t base, uint32_t mod>
bool HashString<base, mod>::operator== (const HashStringSlice<base, mod> & other)
{
    return ((*this)[{0, -1}]) == other;
}

template<uint32_t base, uint32_t mod>
bool HashString<base, mod>::operator!= (const HashStringSlice<base, mod> & other)
{
    return ((*this)[{0, -1}]) != other;
}

}

#endif

using namespace PolynomialHashString;

int main()
{
    std::vector<char> str = {'a','s','j','h','a','b','a','c','a'};
    HashString<> hstr(str);
    cout << (hstr == hstr[{0, -2}]);
    
    return 0;
}