//#include<iostream>
//#include<unordered_map>
//#include <typeindex>
//#include <typeinfo>
//#include<string>
//#include <functional>
//
//template<typename T>
//struct Vtable
//{
//	std::function<void(T*)> foo;
//	std::function<void(T*, int)> bar;
//	Vtable& operator=(const Vtable& other)
//	{
//		foo = other.foo;
//		bar = other.bar;
//		return *this;
//	}
//};
//
//class Entity
//{
//public:
//	int x, y;
//	
//	static Vtable<Entity*> vtable;
//
//	Entity() : x(0) , y(0) {}
//
//	void foo()
//	{
//		std::cout << "[Entity] foo" << std::endl;
//	}
//
//	void bar(int x)
//	{
//		std::cout << "[Entity] bar" << " " << x << std::endl;
//	}
//
//};
//
//class Player : public Entity
//{
//public:
//	int damage;
//
//	static Vtable<Player*> vtable;
//
//	Player() : damage(0) {}
//
//	void foo()
//	{
//		std::cout << "[Player] foo" << std::endl;
//	}
//};
//
//class Enemy : public Entity
//{
//public:
//	int health;
//
//	Enemy() : health(0) {}
//
//	void foo()
//	{
//		std::cout << "[Enemy] foo" << std::endl;
//	}
//};
//
//Vtable Entity::vtable = { &Entity::foo ,Entity::bar };
//
//Vtable Player::vtable = Entity::vtable;
//Vtable Player::vtable = { &Player::foo, &Entity::bar };
//
//int main()
//{
//
//	Player::Vtable::foo = &Player::foo;
//}
//
