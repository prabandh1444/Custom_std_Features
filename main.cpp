#include "type_traits/is_same.h"
#include "type_traits/remove_reference.h"
#include "type_traits/remove_cv.h"
#include "type_traits/typelist.h"
#include "type_traits/Variant.h"
//#include "type_traits/forward.h"
#include "RTTI/Typeinfo.h"
#include "RTTI/Any.h"
#include "RTTI/Function.h"
#include <iostream>
#include <condition_variable>
#include<mutex>

static void test_traits()
{
		//std::cout << is_same<int, int>::value << std::endl;
		//std::cout << is_same<int, const int>::value << std::endl;
		//std::cout << is_same<int, int&>::value << std::endl;

		//std::cout << is_same<int, remove_reference<int>::type> ::value << std::endl;
		//std::cout << is_same<int, remove_reference<int&>::type> ::value << std::endl;
		//std::cout << is_same<int, remove_reference<int&&>::type> ::value << std::endl;
		//// this should be false // 
		//std::cout << is_same<int, remove_reference<const int&>::type> ::value << std::endl;

		/*std::cout << is_same<int, typename remove_cv<const int>::type>::value << std::endl;
		std::cout << is_same<int, typename remove_cv<volatile int>::type>::value << std::endl;
		std::cout << is_same<int, typename remove_cv<const volatile int>::type>::value << std::endl;
		std::cout << is_same<int, typename remove_cv<const int&>::type>::value << std::endl;*/

		/*std::cout << contains<int, typelist<int, std::string, bool>>::value << std::endl;
		std::cout << contains<std::string, typelist<int, std::string, bool>>::value << std::endl;
		std::cout << contains<bool, typelist<int, std::string, bool>>::value << std::endl;
		std::cout << contains<float, typelist<int, std::string, bool>>::value << std::endl;
		std::cout << contains<double, typelist<int, std::string, bool>>::value << std::endl;*/

		/*std::cout << typeid(get<0, typelist<int, std::string, bool>>::type).name() << std::endl;
		std::cout << typeid(get<1, typelist<int, std::string, bool>>::type).name() << std::endl;
		std::cout << typeid(get<2, typelist<int, std::string, bool>>::type).name() << std::endl;

		std::cout << find<int, typelist<int, std::string, bool>>::index << std::endl;
		std::cout << find<std::string, typelist<int, std::string, bool>>::index << std::endl;
		std::cout << find<bool, typelist<int, std::string, bool>>::index << std::endl;
		std::cout << find<float, typelist<int, std::string, bool>>::index << std::endl;
		std::cout << find<double, typelist<int, std::string, bool>>::index << std::endl;*/
}

static void test_concurrency()
{
	std::mutex m;
	std::condition_variable c;
	//c.wait();
	c.notify_one();
}

void func(int& val) { std::cout << "lvalue" << std::endl; }

void func(int&& val) { std::cout << "rvalue" << std::endl; }

void func1(int& x, int & y) { std::cout << "lvalue lvalue" << std::endl; }
void func1(int&& x, int& y) { std::cout << "rvalue lvalue" << std::endl; }
void func1(int& x, int&& y) { std::cout << "rvalue rvalue" << std::endl; }
void func1(int&& x, int&& y) { std::cout << "rvalue rvalue" << std::endl; }


//static void test_semantics()
//{
//	int x = 5;
//	int&& y = 3;
//	func1(forward(x), forward(5));
//	func1(x, y);
//	//func(std::forward(x));
//}

static void test_RTTI()
{
	int x = 5; int y = 3;
	//std::cout << (Typeid(x) == Typeid(y)) << std::endl;
	std::string s = "hello";
	int& mref = x;
	const int& cref = x;
	/*std::cout << (Typeid(x) == Typeid(mref)) << std::endl;
	std::cout << (Typeid(mref) == Typeid(cref)) << std::endl;
	std::cout << (typeid(x) == typeid(s)) << std::endl;*/

	std::cout << (Typeid(x) == Typeid(s)) << std::endl;
	std::cout << (Typeid(x) == Typeid(y)) << std::endl;
	std::cout << (Typeid(x) == Typeid(cref)) << std::endl;
	std::cout << (Typeid(x) == Typeid(mref)) << std::endl;

	std::cout << "#############################################" << std::endl;

	std::cout << (typeid(x) == typeid(s)) << std::endl;
	std::cout << (typeid(x) == typeid(y)) << std::endl;
	std::cout << (typeid(x) == typeid(cref)) << std::endl;
	std::cout << (typeid(x) == typeid(mref)) << std::endl;
}

static void test_any()
{
	Any a = 3.14f;
	std::cout << a.type().name() << " " << any_cast<float>(a) << std::endl;
	Any b = std::string("hello");
	std::cout << b.type().name() << " " << any_cast<std::string>(b) << std::endl;
}

static void test_function()
{
	UniversalFunction<void()> f1 = []() {std::cout << "Hello world" << std::endl; };
	UniversalFunction<void(int, float)> f2 = [](int x, float y) {std::cout << x << " " << y << std::endl; };
	f1();
	f2(2, 0.1f);
}

static void test_variant()
{
	Variant<int, std::string, double> v;
	v = 1;
	int x = Get<int>(v);
	std::cout << x << std::endl;
	v = std::string("hello");
	std::string s = Get<std::string>(v);
	std::cout << s << std::endl;
	v = 0.3f;
	double d = Get<double>(v);
	std::cout << d << std::endl;
}

int main()
{
	//test_traits();
	//test_concurrency();
	//test_semantics();
	//test_RTTI();
	test_variant();
}