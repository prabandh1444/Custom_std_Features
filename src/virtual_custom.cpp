#include<iostream>

class Entity
{
public:
	int x, y;
	void* vptr;

	Entity() : x(0) , y(0) {}

	void foo()
	{
		std::cout << "[Entity] foo" << std::endl;
	}


};

class Player : public Entity
{
public:
	int damage;

	Player() : damage(0) {}

	void foo()
	{
		std::cout << "[Player] foo" << std::endl;
	}
};

class Enemy : public Entity
{
public:
	int health;

	Enemy() : health(0) {}

	void foo()
	{
		std::cout << "[Enemy] foo" << std::endl;
	}
};

int main()
{

}

