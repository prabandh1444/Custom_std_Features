#pragma once
#include "remove_reference.h"

template <typename T>
remove_reference<T>::type&& move(T&& param)
{
	return static_cast<remove_reference<T>::type&&>(param);
}
