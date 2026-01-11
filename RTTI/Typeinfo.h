#pragma once
#include <string>
#include <type_traits>

class TypeinfoProxy
{
public:
	size_t size;
	size_t align;
	TypeinfoProxy() : size(0), align(0) {}
	virtual ~TypeinfoProxy() = default;
};

template <typename T>
class TypeinfoWrapper : public TypeinfoProxy
{
public:
	TypeinfoWrapper() {size = sizeof(T); align = alignof(T); }
};

class Typeinfo
{
public:
	TypeinfoProxy* ptr;

	Typeinfo(TypeinfoProxy* ptr) : ptr(ptr) {}

	Typeinfo() {}

	bool operator==(const Typeinfo& rhs) const { return this->ptr == rhs.ptr; }
	bool operator!=(const Typeinfo& rhs) const { return this->ptr != rhs.ptr; }

	size_t size() const { return ptr->size; }
	size_t align() const { return ptr->align; }
	~Typeinfo() {}
};

template <typename T>
const Typeinfo& Typeid(const T& val)
{
	static TypeinfoWrapper<std::decay_t<T>> type_specific;
	static Typeinfo info = &type_specific;
	return info;
}
