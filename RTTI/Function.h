#pragma once
#include<type_traits>

template<typename R, typename ... Args>
class FunctionBase
{
public:
	virtual R call(Args ... arg) {};
	virtual ~FunctionBase() = default;
};

template <typename F, typename R, typename ... Args>
class FunctionWrapper : public FunctionBase<R, Args ...>
{
private:
	F callable;
public:
	FunctionWrapper(F callable) : callable(std::move(callable)) {}
	R call(Args ... arg) { return callable(arg ...); }

};

template <typename T>
class UniversalFunction;

template <typename R, typename ... Args>
class UniversalFunction<R(Args ...)>
{
private:
	FunctionBase<R, Args ...>* callable;
public:
	template <typename F>
	UniversalFunction(F callable) : callable(reinterpret_cast<FunctionBase<R, Args ...>*>(new FunctionWrapper<F, R, Args ...> (callable))) {}
	R operator()(Args ... arg) { return callable->call(arg ...); }
};
