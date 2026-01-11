#pragma once

template <typename T, typename U>
class is_same
{
public:
	static const bool value = false;
};

template <typename T>
class is_same<T, T>
{
public:
	static const bool value = true;
};

//template <typename T, typename U>
//bool sametype(const T& a, const U& b)
//{
//	return std::is_same<typename std::decay<T>::type, typename std::decay<U>::type>::value;
//}