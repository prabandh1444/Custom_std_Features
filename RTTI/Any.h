#pragma once
#include <typeinfo>

class AnyProxy
{
public:
	virtual const std::type_info& type() = 0;
	virtual ~AnyProxy() = default;
};


template <typename T>
class AnyProxyWrapper : public AnyProxy
{
public:
	T obj;
	AnyProxyWrapper(const T& obj) : obj(obj) {}
	AnyProxyWrapper(T&& obj) : obj(std::move(obj)) {}

	const std::type_info& type() override { return typeid(T); }

	~AnyProxyWrapper() = default;
};

class Any
{
public:
	AnyProxy* ptr;

	Any() : ptr(nullptr) {}

	template <typename T>
	Any(const T& obj) : ptr(reinterpret_cast<AnyProxy*>(new AnyProxyWrapper<T>(obj))) {}

	template <typename T>
	Any(T&& obj) : ptr(reinterpret_cast<AnyProxy*>(new AnyProxyWrapper<T>(std::move(obj)))) {}

	bool has_value() { return ptr != nullptr; }

	const std::type_info& type() { return ptr->type(); }

	
	~Any() { delete ptr; }
};

template <typename T>
T any_cast(const Any& a)
{
	AnyProxyWrapper<T>* ptr = reinterpret_cast<AnyProxyWrapper<T>*>(a.ptr);
	return T(ptr->obj);
}