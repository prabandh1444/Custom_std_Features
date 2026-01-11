#pragma once
template <typename T>
class remove_cv
{
public:
	typedef T type;
};

template <typename T>
class remove_cv<const T>
{
public:
	typedef T type;
};

template <typename T>
class remove_cv<volatile T>
{
public:
	typedef T type;
};

template <typename T>
class remove_cv<const volatile T>
{
public:
	typedef T type;
};