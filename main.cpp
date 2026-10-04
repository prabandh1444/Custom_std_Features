#include "type_traits/is_same.h"
#include "type_traits/remove_reference.h"
#include "type_traits/remove_cv.h"
#include "type_traits/typelist.h"
//#include "type_traits/Variant.h"
#include "type_traits/Rank.h"
#include "type_traits/Vector.h"
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

//static void test_variant()
//{
//	Variant<int, std::string, double> v;
//	v = 1;
//	int x = Get<int>(v);
//	std::cout << x << std::endl;
//	v = std::string("hello");
//	std::string s = Get<std::string>(v);
//	std::cout << s << std::endl;
//	v = 0.3f;
//	double d = Get<double>(v);
//	std::cout << d << std::endl;
//}

//static void test_Rank()
//{
//	std::cout << Rank<int [5][6][7]>::value << std::endl;
//	std::cout << Rank<int [5][6]>::value << std::endl;
//	std::cout << Rank<int [5]>::value << std::endl;
//}

static void test_Vector()
{
	using vec = Vector<1, 2, 3, 4>;
	Print<vec>::f();
	using vec1 = PrependT<0, vec>;
	Print<vec1>::f();
	/*using vec2 = AppendT<5, vec>;
	Print<vec2>::f();
	using vec3 = RemoveFirstT<vec2>;
	Print<vec3>::f();
	using vec4 = RemoveAllT<vec3>;
	Print<vec4>::f();*/
	
	/*std::cout << length<vec> << std::endl;
	std::cout << minimum<vec> << std::endl;*/

	Print<PrefixT<2, vec>>::f();
	Print<ReverseT<vec>>::f();
	Print<SuffixT<0, vec>>::f();
	Print<MergeT<vec, vec1>>::f();

	Print<SortT<Vector <4, 1, 2, 5, 6, 3>>>::f();
	Print<SortT<Vector <3, 3, 1, 1, 2, 2>>>::f();
	Print<SortT<Vector <2, 2, 1, 1, 3, 3>>>::f();

	Print<UniqueT<Vector<1, 1, 2, 2, 2, 1, 1>>>::f();

	 static_assert(Get<0, Vector<0,1,2>>::value == 0);
	 static_assert(Get<1, Vector<0,1,2>>::value == 1);
	 static_assert(Get<2, Vector<0,1,2>>::value == 2);
	 
	 std::cout << LowerBound<3, Vector<0, 1, 2, 3, 4>> << std::endl;
	 std::cout << LowerBound<3, Vector<0, 1, 2, 4, 5>> << std::endl;
	 std::cout << LowerBound<9, Vector<0, 1, 2, 4, 5>> << std::endl;
	 std::cout << LowerBound<-1, Vector<0, 1, 2, 4, 5>> << std::endl;
	 std::cout << LowerBound<2, Vector<0, 2, 2, 2, 2, 2>> << std::endl;

	 Print<ConcatT<Vector<1, 2>, Vector<3, 4>>>::f();

	 Print<RLET<Vector<0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1>>>::f();
	 Print<RLET<Vector<1, 1, 1, 1, 9, 9, 9, 2>>>::f();
}

int main()
{
	//test_traits();
	//test_concurrency();
	//test_semantics();
	//test_RTTI();
	//test_variant();
	//test_Rank();
	test_Vector();
}