#pragma once

template <bool b, typename T>
struct enable_if
{

};

template <typename T>
struct enable_if<true, T>
{
	typedef T type;
};

