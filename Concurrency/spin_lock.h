#pragma once

class Mutex
{
	bool lock;

public:
	Mutex() : lock(false) {}
	bool aquire() 
	{
		while (xchng(lock, 1));
	}

	bool release() { lock = false; }
};


#include <condition_variable>

std::condition_variable c;

