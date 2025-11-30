#include <utility>
#include <iostream>
#include <map>

class Point
{
public:
	int x, y;
};

template <typename T>
class Unique_Pointer
{
private:
	T* ptr;

public:
	Unique_Pointer() : ptr(nullptr) {}
	Unique_Pointer(T* ptr) : ptr(ptr) {}
	Unique_Pointer(Unique_Pointer<T>& other) = delete;	
	Unique_Pointer(Unique_Pointer<T>&& other)
	{
		ptr       = other.ptr;
		other.ptr = nullptr;
	}

	Unique_Pointer<T>& operator=(const Unique_Pointer<T>& other) = delete;
	Unique_Pointer<T>& operator=(Unique_Pointer<T>&& other)
	{
		ptr = other.ptr;
		other.ptr = nullptr;
		return *this;
	}

	void swap(Unique_Pointer<T>& other)
	{
		T* old = ptr;
		ptr = other.ptr;
		other.ptr = old;
		return;

	}
	T* release()
	{
		T* temp = ptr;
		ptr = nullptr;
		return temp;
	}
	void reset(const T* new_ptr)
	{
		delete ptr;
		ptr = new_ptr;
	}

	const T& operator*() const { return *ptr; }
	const T* operator->() const { return ptr; }

	T& operator*() { return *ptr; }
	T* operator->() { return ptr; }

	~Unique_Pointer()
	{
		delete ptr;
	}

};

class ControlBlock
{
public:
	int weak_count;
	int strong_count;

	ControlBlock() : weak_count(0), strong_count(0) {}
};

template <typename T>
class Shared_Pointer
{
public:
	T* ptr;
	static std::map<T*, ControlBlock> control_map;

	Shared_Pointer() : ptr(nullptr) {}
	Shared_Pointer(T* ptr) : ptr(ptr) { control_map[ptr].strong_count++; }
	Shared_Pointer(const Shared_Pointer<T>& other)
	{
		ptr = other.ptr;
		control_map[ptr].strong_count++;
	}
	Shared_Pointer(Shared_Pointer<T>&& other)
	{
		if (--control_map[ptr].strong_count == 0) delete ptr;
		ptr = other.ptr;
		other.ptr = nullptr;
	}

	Shared_Pointer<T>& operator=(const Shared_Pointer<T>& other)
	{
		if (this == other) return *this;
		if (--control_map[ptr].strong_count == 0) delete ptr;
		ptr = other.ptr;
		control_map[ptr].strong_count++;
		return *this;
	}
	Shared_Pointer<T>& operator=(Shared_Pointer&& other)
	{
		if (this == other) return *this;
		if (--control_map[ptr].strong_count == 0) delete ptr;
		ptr       = other.ptr;
		other.ptr = nullptr;
		return *this;
	}

	void reset()
	{
		if (--control_map[ptr].strong_count == 0) delete ptr;
		ptr = nullptr;
	}
	void swap(Shared_Pointer<T>& other)
	{
		T* temp   = ptr;
		ptr       = other.ptr;
		other.ptr = temp;
	}

	const T& operator*()  const { return *ptr; }
	const T* operator->() const { return ptr; }
	T& operator*() { return *ptr; }
	T* operator->() { return ptr; }

	size_t use_count()       const { return control_map[ptr].strong_count; }

	~Shared_Pointer()
	{
		if (--control_map[ptr].strong_count == 0) delete ptr;
	}

};

template <typename T>
class Weak_Pointer
{
private:
	T* ptr;

public:
	Weak_Pointer() : ptr(nullptr) {}
	Weak_Pointer(const Shared_Pointer<T>& other)
	{
		ptr = other.ptr;
		Shared_Pointer<T>::control_map[ptr].weak_count++;
	}
	Weak_Pointer(const Weak_Pointer<T>& other)
	{
		Shared_Pointer<T>::control_map[ptr].weak_count--;
		ptr = other.ptr;
		Shared_Pointer<T>::control_map[ptr].weak_count++;
	}
	
	Weak_Pointer<T>& operator=(const Weak_Pointer<T>& other)
	{
		Shared_Pointer<T>::control_map[ptr].weak_count--;
		ptr = other.ptr;
		Shared_Pointer<T>::control_map[ptr].weak_count++;
		return *this;
	}
	Weak_Pointer<T>& operator=(const Shared_Pointer<T>& other)
	{
		ptr = other.ptr;
		Shared_Pointer<T>::control_map[ptr].weak_count++;
		return *this;
	}
	Weak_Pointer<T>& operator=(Weak_Pointer&& other)
	{
		if (this == other) return *this;
		Shared_Pointer<T>::control_map[ptr].weak_count--;
		ptr = other.ptr;
		other.ptr = nullptr;
		return *this;
	}

	void reset()
	{
		Shared_Pointer<T>::control_map[ptr].weak_count--;
		ptr = nullptr;
	}

	Shared_Pointer<T> lock()
	{
		if (expired())
		{
			std::cerr << "Strong Point cant be init as no reference left" << std::endl;
		}

		return Shared_Pointer<T>(ptr);
	}

	bool  expired() const { return Shared_Pointer<T>::control_map[ptr].strong_count == 0; }
	size_t use_count() const { return Shared_Pointer<T>::control_map[ptr].strong_count; }

	~Weak_Pointer() {};

};

template <typename T, typename ... Args>
static Unique_Pointer<T> make_unique(Args&& ... args)
{
	return Unique_Pointer(new T(std::forward<Args>(args)...));
}

template <typename T, typename ... Args>
static Shared_Pointer<T> make_shared(Args&& ... args)
{
	return Shared_Pointer(new T(std::forward<Args>(args)...));
}

template <typename T>
std::map<T*, ControlBlock> Shared_Pointer<T>::control_map = {};

//int main()
//{
//	//Unique_Pointer<Point> ptr1 = make_unique<Point>(2, 3);
//	//Unique_Pointer<Point> ptr2 = make_unique<Point>(4, 5);
//	// //Unique_Pointer<Point> ptr1 = ptr2;
//	//Unique_Pointer<Point> ptr = std::move(ptr2);
//	//ptr1.swap(ptr);
//	//std::cout << ptr1->x << " " << ptr1->y << std::endl;
//	//std::cout << ptr->x << " " << ptr->y << std::endl;
//
//	Weak_Pointer<Point> wptr;
//	{
//		Shared_Pointer<Point> ptr = make_shared<Point>(2, 3);
//		Shared_Pointer<Point> ptr1 = ptr;
//		std::cout << ptr.use_count() << std::endl;
//		Shared_Pointer<Point> ptr2 = std::move(ptr);
//		std::cout << ptr2.use_count() << std::endl;
//		wptr = ptr1;
//		std::cout << wptr.use_count() << std::endl;
//		Shared_Pointer<Point> sp = wptr.lock();
//		std::cout <<sp.use_count() << " "<<sp->x<<" "<<sp->y << std::endl;
//	}
//	std::cout << wptr.use_count() << std::endl;
//	Weak_Pointer<Point> wptr1 = make_shared<Point>(4,5);
//	std::cout << wptr1.use_count() << std::endl;
//}