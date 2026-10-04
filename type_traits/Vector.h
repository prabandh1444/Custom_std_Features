#pragma once
#include <iostream>
#include <algorithm>

template<typename>
inline constexpr bool dependent_false_v = false;

template <int ... vals>
struct Vector;

template <typename T>
struct Print;

template <>
struct Print<Vector<>>
{
	static void f()
	{
		std::cout << "\n";
	}
};

template <int head, int ... tail>
struct Print<Vector<head, tail ...>>
{
	static void f()
	{
		std::cout << head << " ";
		Print<Vector<tail...>>::f();
	}
	
};

template <int val, typename T>
struct Prepend;

template <int val, int ... vals>
struct Prepend<val, Vector<vals...>>
{
	typedef Vector<val, vals...> type;
};

template <int val, typename T>
using PrependT = Prepend<val, T>::type;

template <int val, typename T>
struct Append;

template <int val, int ... vals>
struct Append < val, Vector<vals...>>
{
	typedef Vector<vals..., val> type;
};

template <int val, typename T>
using AppendT = Append<val, T>::type;

template <typename T>
struct RemoveFirst;

template <>
struct RemoveFirst<Vector<>>
{
	//static_assert(dependent_false_v<Vector<>>, "Can't remove element from an  empty vector");
};

template <int val, int ... vals>
struct RemoveFirst<Vector<val, vals...>>
{
	typedef Vector<vals...> type;
};

template <typename T>
using RemoveFirstT = RemoveFirst<T>::type;


template <typename T>
struct RemoveAll;

template <int ... vals>
struct RemoveAll <Vector<vals...>>
{
	typedef Vector<> type;
};

template <typename T>
using RemoveAllT = RemoveAll<T>::type;

template <typename T>
struct Length;

template <>
struct Length<Vector<>>
{
	static constexpr size_t value = 0;
};

template <int val, int ... vals>
struct Length<Vector<val, vals...>>
{
	static constexpr size_t value = 1ull + Length<Vector<vals...>>::value;
};

template <typename T>
constexpr size_t length = Length<T>::value;

template <typename T>
struct Min;

template <int ... vals>
struct Min<Vector<vals ...>>
{
	static constexpr size_t value = std::min({ vals ... });
};

template <typename T>
constexpr size_t minimum = Min<T>::value;

template <size_t idx, typename T>
struct Prefix;

template <>
struct Prefix<0, Vector<>>
{
	typedef Vector<> type;
};

template <int val, int ... vals>
struct Prefix<0, Vector<val, vals...>>
{
	typedef Vector<> type;
};

template <size_t idx, int val, int ... vals>
struct Prefix<idx, Vector<val, vals...>>
{
	typedef PrependT<val, typename Prefix<idx-1, Vector<vals...>>::type> type;
};

template <size_t idx, typename T>
using PrefixT = Prefix<idx, T>::type;

template <typename T>
struct Reverse;

template <>
struct Reverse<Vector<>>
{
	typedef Vector<> type;
};

template <int val, int ... vals>
struct Reverse<Vector<val, vals...>>
{
	typedef AppendT<val, typename Reverse<Vector<vals...>>::type> type;
};

template <typename T>
using ReverseT = Reverse<T>::type;


template <size_t idx, typename T>
using SuffixT = ReverseT<PrefixT<idx, ReverseT<T>>>;

template <typename T, typename U>
struct Merge;

template <>
struct Merge<Vector<>, Vector<>>
{
	typedef Vector<> type;
};

template <typename T>
struct Merge<Vector<>, T>
{
	typedef T type;
};

template <typename U>
struct Merge<U, Vector<>>
{
	typedef U type;
};

template <int val1, int val2, int ... vals1, int ... vals2>
struct Merge < Vector<val1, vals1...>, Vector<val2, vals2...>>
{
	typedef PrependT<val1, typename Merge<Vector<vals1...>, Vector<val2, vals2...>>::type> type1;
	typedef PrependT<val2, typename Merge<Vector <val1, vals1...>, Vector<vals2...>>::type> type2;
	typedef std::conditional<val1<val2, typename type1, typename type2>::type type;
};

template <typename T, typename U>
using MergeT = Merge<T, U>::type;

template <typename T>
struct Sort;

template <>
struct Sort<Vector<>>
{
	typedef Vector<> type;
};

template <int val>
struct Sort<Vector<val>>
{
	typedef Vector<val> type;
};

template <int ... vals>
struct Sort<Vector<vals...>>
{
	static constexpr size_t sz = length<Vector<vals...>>;
	static constexpr size_t sz1 = sz/2;
	static constexpr size_t sz2 = sz-sz1;
	typedef Sort<PrefixT<sz1, typename Vector<vals...>>>::type type1;
	typedef Sort<SuffixT<sz2, typename Vector<vals...>>>::type type2;
	typedef MergeT<typename type1, typename type2> type;
};

template <typename T>
using SortT = Sort<T>::type;

template <typename T>
struct Unique;

template <>
struct Unique<Vector<>>
{
	typedef Vector<> type;
};

template <int val>
struct Unique<Vector<val>>
{
	typedef Vector<val> type;
};

template <int val1, int val2, int ... vals>
struct Unique<Vector<val1, val2, vals ...>>
{
	typedef Unique<Vector<val2, vals ...>>::type type1;
	/*typedef PrependT<val1, typename Unique<typename Vector<val2, vals ...>>::type> type2;*/
	typedef PrependT<val1, typename Unique<Vector<val2, vals ...>>::type> type2;
	typedef std::conditional<val1==val2, typename type1, typename type2>::type type;
};

template <typename T>
using UniqueT = Unique<T>::type;


template <size_t idx, typename T>
struct Get;

template <int val, int ... vals>
struct Get<0, Vector<val, vals...>>
{
	static constexpr int value = val;
};

template <size_t idx>
struct Get<idx, Vector<>>
{
	static_assert(dependent_false_v<Vector<>>, "Can't get element out of bounds");
};

template <size_t idx, int val, int ... vals>
struct Get<idx, Vector<val, vals...>>
{
	static constexpr int value = Get<idx - 1, Vector<vals...>>::value;
};

template <int val, size_t L, size_t R, typename T>
struct BinarySearch;

template <int val, size_t L, int ... vals>
struct BinarySearch<val, L, L, Vector<vals...>>
{
	static constexpr int value = Get<L, Vector<vals...>>::value;
	static constexpr size_t index = value >= val ? L : L + 1;
};

template <int val, size_t L, size_t R, int ... vals>
struct BinarySearch <val, L, R, Vector<vals...>>
{
	static constexpr size_t M = (L + R) / 2;
	static constexpr int mid = Get<M, Vector<vals...>>::value;
	static constexpr size_t index = mid < val ? BinarySearch<val, M + 1, R, Vector<vals...>>::index : BinarySearch<val, L, M, Vector<vals...>>::index;
};

template <int val, typename T>
constexpr size_t LowerBound =  BinarySearch<val, 0ull, length<T>-1, T>::index;


template <typename T, typename U>
struct Concat;

template <>
struct Concat<Vector<>, Vector<>>
{
	typedef Vector<> type;
};

template <int ... vals>
struct Concat<Vector<vals...>, Vector<>>
{
	typedef Vector<vals...> type;
};

template <int ... vals>
struct Concat<Vector<>, Vector<vals...>>
{
	typedef Vector<vals...> type;
};

template<int val2, int ... vals1, int ... vals2>
struct Concat<Vector<vals1...>, Vector<val2, vals2 ...>>
{
	typedef Concat<Vector<vals1..., val2>, Vector<vals2...>>::type type;
};

template <typename T, typename U>
using ConcatT = Concat<T, U>::type;

template <int count, int prev, typename T>
struct Helper;

template <int count, int prev>
struct Helper<count, prev, Vector<>>
{
	typedef Vector<count, prev> type;
};

template <int count, int prev, int val, int ... vals>
struct Helper<count, prev, Vector<val, vals...>>
{
	typedef Helper <count + 1, prev, Vector<vals...>>::type type1;
	typedef ConcatT<Vector<count, prev>, typename Helper<1, val, Vector<vals...>>::type> type2;
	typedef std::conditional<prev == val, type1, type2>::type type;
};

template <typename T>
struct RLE;

template <>
struct RLE<Vector<>>
{
	typedef Vector<> type;
};

template <int val, int ... vals>
struct RLE<Vector<val, vals...>>
{
	typedef Helper < 1, val, Vector < vals...>>::type type;
};

template <typename T>
using RLET = RLE<T>::type;

