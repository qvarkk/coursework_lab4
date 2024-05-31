#pragma once

#include <string>
#include <iostream>

template<size_t N>
class bitset {
private:
	static const size_t bitsPerWord = sizeof(unsigned int) * 8;
	static const size_t _size = (N + bitsPerWord - 1) / bitsPerWord;
	unsigned int bits[_size] = { 0 };
public:
	bitset() {};

	// Check if all bits in a bitset are set to 1.
	bool all() const;
	// Check if any bit in a bitset in set to 1.
	bool any() const;
	// Check if none of the bits in a bitset are set to 1.
	bool none() const;
	// Check if a bit at a specified position in a bitset is set to 1.
	bool test(size_t pos) const;

	// Returns the number of bits in a bitset object.
	size_t size() const;
	// Returns the number of bits set in a bitset.
	size_t count() const;

	// Inverts the value of all bits in a bitset or inverts a single bit at a specified position.
	bitset<N>& flip();
	bitset<N>& flip(size_t pos);

	// Sets the value of all bits in a bitset or a single bit at a specified position to 1.
	bitset<N>& set();
	bitset<N>& set(size_t pos, bool val = true);

	// Resets the value of all bits in a bitset or a single bit at a specified position to 0.
	bitset<N>& reset();
	bitset<N>& reset(size_t pos);

	// Convert bitset to string
	std::string to_string(char zero = '0', char one = '1');
	// Convert bitset to ullong
	unsigned long long to_ullong() const;
	// Convert bitset to ulong
	unsigned long to_ulong() const;

	bool operator!=(const bitset<N>& right) const;
	bool operator==(const bitset<N>& right) const;

	bitset<N>& operator &= (const bitset<N>& right);
	bitset<N>& operator|=(const bitset<N>& right);
	bitset<N>& operator^=(const bitset<N>& right);

	bitset<N> operator~() const;

	bitset<N> operator<<(size_t pos) const;
	bitset<N> operator>>(size_t pos) const;

	bitset<N>& operator<<=(size_t pos);
	bitset<N>& operator>>=(size_t pos);
	
	bool operator[](size_t pos) const;
};

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
    } else {
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
    } else {
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
        if (this->test(i) != right.test(i)) {
            return true;
        }
    }
    return false;
}

template<size_t N>
bool bitset<N>::operator==(const bitset<N>& right) const {
    for (int i = 0; i < N; i++) {
        if (this->test(i) != right.test(i)) {
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
    bitset<N> result;
    if (pos >= N) return result;

    size_t wordShift = pos / bitsPerWord;
    size_t bitShift = pos % bitsPerWord;

    for (size_t i = _size; i > wordShift; i--) {
        result.bits[i - 1] = bits[i - 1 - wordShift] << bitShift;
        if (i > wordShift + 1 && bitShift > 0) {
            result.bits[i - 1] |= bits[i - 2 - wordShift] >> (bitsPerWord - bitShift);
        }
    }
    return result;
}

template<size_t N>
bitset<N> bitset<N>::operator>>(size_t pos) const {
    bitset<N> result;
    if (pos >= N) return result;

    size_t wordShift = pos / bitsPerWord;
    size_t bitShift = pos % bitsPerWord;

    for (size_t i = 0; i < _size - wordShift; ++i) {
        result.bits[i] = bits[i + wordShift] >> bitShift;
        if (i + wordShift + 1 < _size && bitShift > 0) {
            result.bits[i] |= bits[i + wordShift + 1] << (bitsPerWord - bitShift);
        }
    }
    return result;
}

template<size_t N>
bitset<N>& bitset<N>::operator<<=(size_t pos) {
    *this = *this << pos;
    return *this;
}

template<size_t N>
bitset<N>& bitset<N>::operator>>=(size_t pos) {
    *this = *this >> pos;
    return *this;
}

template<size_t N>
bool bitset<N>::operator[](size_t pos) const {
    return test(pos);
}
