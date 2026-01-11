#pragma once
#include <algorithm>
#include <type_traits>

template <typename ... Ts>
struct typelist;

template <typename T, typename List>
struct contains;

template <typename T>
struct contains<T, typelist<>>
{
	static constexpr bool value = false;
};

template <typename T, typename head, typename ... tail>
struct contains<T, typelist<head, tail...>>
{
	static constexpr bool value = std::is_same<head, T>::value || contains<T, typelist<tail...>>::value;
};

template <size_t index, typename T>
struct get {};

template <typename head, typename ... tail>
struct get<0, typelist<head, tail ...>>
{
	typedef head type;
};

template <size_t index, typename head, typename ... tail>
struct get<index, typelist<head, tail ...>>
{
	typedef get<index - 1, typelist<tail...>>::type type;
};

template <typename T, typename List>
struct find;

template <typename T>
struct find<T, typelist<>>
{
	static constexpr size_t index = -100;
};

template <typename T, typename head, typename ... tail>
struct find<T, typelist<head, tail...>>
{
	static constexpr size_t index = std::is_same<T, head>::value ? 0 : 1+find<T, typelist<tail...>>::index;
};
