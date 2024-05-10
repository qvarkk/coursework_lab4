#ifndef BITSET_H
#define BITSET_H

template<size_t N>
class bitset {
private:
	static const size_t bitsPerWord = sizeof(unsigned int) * 8;
	static const size_t _size = (N + bitsPerWord - 1) / bitsPerWord;
	unsigned int bits[_size] = { 0 };
public:
	bitset() {};

	// Print every bit
	void print() const;

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

	bool operator != (const bitset<N>& right) const;
	bool operator==(const bitset<N>& right) const;

	bitset<N>& operator &= (const bitset<N>& right);
	bitset<N>& operator|=(const bitset<N>& right);
	bitset<N>& operator^=(const bitset<N>& right);

	bitset<N> operator~() const;

	bitset<N> operator << (size_t pos) const;
	bitset<N> operator>>(size_t pos) const;

	bitset<N>& operator<<=(size_t pos);
	bitset<N>& operator>>=(size_t pos);
	
	bool operator[](size_t pos) const;
};

#endif