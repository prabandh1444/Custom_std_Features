#pragma once
template <typename T>
struct Rank
{
	static constexpr size_t value = 0;
};

template <typename T, size_t idx>
struct Rank<T[idx]>
{
	static constexpr size_t value = 1 + Rank<T>::value;
};
