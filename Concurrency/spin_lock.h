#pragma once
#include <atomic>

class Mutex
{
	std::atomic<bool> lock;

public:
	Mutex() : lock(false) {}
	bool aquire() 
	{
		while (lock.exchange(true, std::memory_order_acquire));
	}

	bool release() { lock.store(false, std::memory_order_release); }
};


