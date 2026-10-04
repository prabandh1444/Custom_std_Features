#pragma once

template <typename T>
class UniqueLock
{
	T& lock;
public:
	UniqueLock(const T& lock) lock(lock) {};
	UniqueLock(const UniqueLock& other) = delete;
	UniqueLock(UniqueLock&& other) = delete;
};