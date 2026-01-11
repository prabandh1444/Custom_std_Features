#pragma once
#include "remove_reference.h"
#include "is_same.h"
#include <utility>

template <typename T>
T&& forward(T&& param)
{
	if (is_same<T, typename remove_reference<T>::type>::value) return static_cast<T&&>(param);
	else return param;
}