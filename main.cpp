#include "bitset.h"
#include <iostream>
#include <string>
#include <bitset>

int main() {
    std::bitset<9> bitset;

    
}

template<size_t N>
bool bitset<N>::all() const {
    for (size_t i = 0; i < _size - 1; i++) {
        if (bits[i] != ~0u) {
            return false;
        }
    }

    for (size_t i = (_size - 1) * bitsPerWord; i < N; i++) {
        if (!test(i)) {
            return false;
        }
    }

    return true;
}

template<size_t N>
bool bitset<N>::any() const {
    for (size_t i = 0; i < _size; i++) {
        if (bits[i] != 0) {
            return true;
        }
    }

    return false;
}

template<size_t N>
bool bitset<N>::none() const {
    return !any();
}

template<size_t N>
bool bitset<N>::test(size_t pos) const {
    if (pos >= N)
        throw std::out_of_range("bitset::test");

    return (bits[pos / bitsPerWord] >> (pos % bitsPerWord)) & 1u;
}

template<size_t N>
size_t bitset<N>::size() const {
    return N;
}

template<size_t N>
size_t bitset<N>::count() const {
    size_t count = 0;
    for (size_t i = 0; i < N; i++)
        count += test(i);

    return count;
}

template<size_t N>
bitset<N>& bitset<N>::flip() {
    for (int i = 0; i < _size; i++) {
        bits[i] = ~bits[i];
    }
    return *this;
}

template<size_t N>
bitset<N>& bitset<N>::flip(size_t pos) {
    if (pos >= N)
        throw std::out_of_range("bitset::flip");

    if (test(pos)) {
        reset(pos);
    }
    else {
        set(pos);
    }
}

template<size_t N>
bitset<N>& bitset<N>::set() {
    for (size_t i = 0; i < _size; i++) {
        bits[i] = ~0u;
    }
    return *this;
}

template<size_t N>
bitset<N>& bitset<N>::set(size_t pos, bool val) {
    if (pos >= N)
        throw std::out_of_range("bitset::set");

    if (val) {
        bits[pos / bitsPerWord] |= (1u << (pos % bitsPerWord));
    }
    else {
        bits[pos / bitsPerWord] &= ~(1u << (pos % bitsPerWord));
    }
    return *this;
}

template<size_t N>
bitset<N>& bitset<N>::reset() {
    for (size_t i = 0; i < _size; ++i) {
        bits[i] = 0u;
    }
    return *this;
}

template<size_t N>
bitset<N>& bitset<N>::reset(size_t pos) {
    if (pos >= N)
        throw std::out_of_range("bitset::reset");

    bits[pos / bitsPerWord] &= ~(1u << (pos % bitsPerWord));
    return *this;
}

template<size_t N>
std::string bitset<N>::to_string(char zero, char one) {
    if (zero == one) {
        throw std::invalid_argument("zero and one characters must be different");
    }

    std::string result;
    result.reserve(N);
    for (size_t i = N; i > 0; i--) {
        result.push_back(test(i - 1) ? one : zero);
    }

    return result;
}

template<size_t N>
unsigned long long bitset<N>::to_ullong() const {
    if (N > sizeof(unsigned long long) * 8) {
        throw std::overflow_error("bitset size exceeds the size of unsigned long long");
    }

    unsigned long long result = 0;
    for (size_t i = 0; i < N; ++i) {
        if (test(i)) {
            result |= (1ull << i);
        }
    }
    return result;
}

template<size_t N>
unsigned long bitset<N>::to_ulong() const {
    if (N > sizeof(unsigned long) * 8) {
        throw std::overflow_error("bitset size exceeds the size of unsigned long long");
    }

    unsigned long result = 0;
    for (size_t i = 0; i < N; ++i) {
        if (test(i)) {
            result |= (1ul << i);
        }
    }
    return result;
}

template<size_t N>
bool bitset<N>::operator!=(const bitset<N>& right) const {
    for (int i = 0; i < N; i++) {
        if (this->test(i) == right.test(i)) {
            return false;
        }
    }
    return true;
}

template<size_t N>
bool bitset<N>::operator==(const bitset<N>& right) const {
    for (int i = 0; i < N; i++) {
        if (bits[i] == right.bits[i]) {
            return false;
        }
    }
    return true;
}

template<size_t N>
bitset<N>& bitset<N>::operator&=(const bitset<N>& right) {
    for (size_t i = 0; i < bitsPerWord; ++i) {
        bits[i] &= right.bits[i];
    }
    return *this;
}

template<size_t N>
bitset<N>& bitset<N>::operator|=(const bitset<N>& right) {
    for (size_t i = 0; i < bitsPerWord; ++i) {
        bits[i] |= right.bits[i];
    }
    return *this;
}

template<size_t N>
bitset<N>& bitset<N>::operator^=(const bitset<N>& right) {
    for (size_t i = 0; i < bitsPerWord; ++i) {
        bits[i] ^= right.bits[i];
    }
    return *this;
}

template<size_t N>
bitset<N> bitset<N>::operator~() const {
    for (size_t i = 0; i < bitsPerWord; ++i) {
        bits[i] = ~bits[i];
    }
    return *this;
}

template<size_t N>
bitset<N> bitset<N>::operator<<(size_t pos) const {
    // Implementation for operator<<
}

template<size_t N>
bitset<N> bitset<N>::operator>>(size_t pos) const {
    // Implementation for operator>>
}

template<size_t N>
bitset<N>& bitset<N>::operator<<=(size_t pos) {
    // Implementation for operator<<=
}

template<size_t N>
bitset<N>& bitset<N>::operator>>=(size_t pos) {
    // Implementation for operator>>=
}

template<size_t N>
bool bitset<N>::operator[](size_t pos) const {
    return test(pos);
}


