#pragma once
#include <algorithm>
#include <utility>
#include <stdexcept>
#include "typelist.h"


template <typename ... Ts>
class Variant
{
public:
	size_t index;
	static constexpr size_t max_size = std::max({ sizeof(Ts)... });
	static constexpr size_t max_allign = std::max({ alignof(Ts)...});

	alignas(max_allign) std::byte buffer[max_size];

	Variant() : index(-1) {};

	template <typename T>
	Variant(const T& val)
	{
		static_assert(contains<T, typelist<Ts...>>::value, "cannot initialize the objct as type is one of the types in the typelist");
		index = find<T, typelist<Ts...>>::index;
		new (buffer) T(val);
	}

	template <typename T>
	Variant(T&& val)
	{
		static_assert(contains<T, typelist<Ts...>>::value, "cannot initialize the objct as type is one of the types in the typelist");
		index = find<T, typelist<Ts...>>::index;
		new (buffer) T(std::move(val));
	}

	Variant(const Variant& other)
	{
		using T = get<other.index, typelist<Ts...>>::type;
		index = other.index;
		new (&buffer) T(*(reinterpret_cast<T*>(other.buffer)));
	}

	Variant(Variant&& other)
	{
		using T = get<other.index, typelist<Ts...>>::type;
		index = other.index;
		new (buffer) T(std::move(*(reinterpret_cast<T*>(other.buffer))));
		other.destroy();
	}

	Variant& operator=(const Variant& other)
	{
		if (this == &other) return *this;
		destroy();
		using T = get<other.index, typelist<Ts...>>::type;
		index = other.index;
		new (buffer) T(*(reinterpret_cast<T*>(other.buffer)));
		return *this;
	}

	Variant& operator=(const Variant&& other)
	{
		if (this == &other) return *this;
		destroy();
		using T = get<other.index, typelist<Ts...>>::type;
		index = other.index;
		new (buffer) T(*(reinterpret_cast<T*>(other.buffer)));
		other.destroy();
		return *this;
	}

	template <typename T>
	Variant& operator=(const T& val)
	{
		destroy();
		index = find<T, typelist<Ts...>>::index;
		new (buffer) T(val);
	}

	template <typename T>
	Variant& operator=(T&& val)
	{
		destroy();
		index = find<T, typelist<Ts...>>::index;
		new (buffer) T(std::move(val));
	}

	void destroy()
	{
		if (index == -1) return;
		using T = get<index, typelist<Ts...>>::type;
		reinterpret_cast<T*>(buffer)->~T();
		index = -1;
	}

	~Variant() { destroy(); }
};

template <typename T, typename ... Ts>
T Get(Variant<Ts ...>& v)
{
	static_assert(contains<T, typelist<Ts...>>::value, "cannot initialize the objct as type is one of the types in the typelist");
	return T(*(reinterpret_cast<T*>(v.buffer)));
}

template <size_t index, typename ... Ts>
get<index, typelist<Ts...>>::type Get(Variant<Ts ...>& v)
{
	//static_assert(index == v.index, "cannot cast into type T");
	using T = get<index, typelist<Ts...>>::type;
	return T(*(reinterpret_cast<T*>(v.buffer)));
}