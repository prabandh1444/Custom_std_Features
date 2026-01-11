#pragma once
template <typename T>
class remove_reference
{
public:
	typedef T type;
};

template <typename T>
class remove_reference<T&>
{
public:
	typedef T type;
};

template <typename T>
class remove_reference<T&&>
{
public:
	typedef T type;
};