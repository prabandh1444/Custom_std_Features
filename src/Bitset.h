#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

char _UNSIGNED_LONG_LONG_SIZE = 64;

template <size_t N>
class Bitset
{
private:
	constexpr size_t capacity = (N + 3) & ~(3ull);
	constexpr size_t words = (capacity >> 2);
	char resource[capacity];
	size_t set_count;

public:
	Bitset() 
	{
		std::memset(resource, 0, capacity);
		set_count = 0;
	}
	Bitset(unsigned long long value)
	{
		if (N < _UNSIGNED_LONG_LONG_SIZE) [[unlikey]]
		{
			throw std::runtime_error("Can't intialize a bitset with less size than N.");
		}
		std::memset(resource, 0, capacity);
		*((unsigned long long*)resource) = value;
		set_count = __builltin_popcountull(value);
	}
	Bitset(const std::string& value)
	{
		std::memset(resource, 0, capacity);
		set_count = 0;
		size_t length = value.length();
		if (N < length) [[unlikey]]
		{
			throw std::runtime_error("Can't intialize a bitset with less size than N.");
		}
		for (size_t idx = 0; idx < length; idx++)
		{
			if (value[idx] != '0' && value[idx] != '1') [[unlikey]]
			{
				throw std::runtime_error("Can be only 0's and 1's.")
			}
			if (value[idx] == '1') set_count++;
			resource[length - idx - 1] = value[idx] - '0';
		}
	}
	Bitset(const Bitset& other)
	{
		assert(capacity == other.capacity, "This can't happen");
		std::memcpy(resource, other.resource, other.capacity);
		set_count = other.set_count;
	}
	Bitset& operator=(const Bitset& other)
	{
		if (this == other) return *this;
		std::memcpy(resource, other.resource, other.capacity);
	}
	bool operator==(const Bitset& lhs, const Bitset& rhs)
	{
		return (lhs.capacity == rhs.capacity) &&
			(memcmp(lhs.resource, rhs.resource, lhs.capacity==0);
	}
	bool operator[](const size_t idx)
	{
		char offset = idx % 4; int index = idx / 4;
		return resource[index] & (1 << offset);
	}

	size_t size() const { return N; }
	size_t count() const { return set_count; }
	bool all() const { return set_count == N; }
	bool any() const { return set_count > 0;}
	bool none() const {return set_count == 0;}

	
	void set()
	{
		memset(resource, 1, capacity);
		set_count = N;
	}
	void reset()
	{
		memset(resource, 0, capacity);
		set_count = 0;
	}
	void flip()
	{
		for (idx = 0; idx < words; idx++)
		{
			resource[idx] = (0xF) ^ resource[idx];
		}
	}

};