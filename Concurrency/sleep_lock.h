#pragma once
#include <atomic>


class SleepLock
{
	std::atomic_flag lock;
public:
	SleepLock() : lock(ATOMIC_FLAG_INIT) {}

	void aquire() { while (lock.test_and_set(std::memory_order_acquire)) { lock.wait(true, std::memory_order_relaxed); } }

	void release() { lock.clear(); lock.notify_one(); }
};
