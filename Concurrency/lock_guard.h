#pragma once

template <typename T>
class LockGuard
{
	T& lock;
public:
	LockGuard(const T& lock) lock(lock) {lock.lock() };

	LockGuard(const LockGuard& other) = delete;
	LockGuard(LockGuard&& other) = delete;
	
	~LockGuard() { lock.unlock(); }
};
