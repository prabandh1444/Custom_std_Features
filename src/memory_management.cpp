#include <iostream>
#include <stdexcept>
#include <set>

class MemoryManagement
{
private:
	void* resource;
	int max_sz;
	std::set<std::pair<int, void*>> freelist;
	std::set<std::pair<void*, int>> inverse_freelist;


public:
	MemoryManagement() : resource(new char[1000]), max_sz(1000) { freelist.insert({ 1000, resource }); inverse_freelist.insert({ resource, 1000 }); }
	MemoryManagement(int tot_sz) : resource(new char[tot_sz]), max_sz(tot_sz) { freelist.insert({ tot_sz, resource }); inverse_freelist.insert({ resource, tot_sz });}

	void* malloc(int sz)
	{
		int req = sz + 4;
		auto it = freelist.lower_bound({ req, nullptr });
		if (it == freelist.end()) throw std::runtime_error("No continous memory is found");
		
		int avail = it->first; void* ptr = it->second;
		*(int*)ptr = sz;
		ptr = (char*)ptr+4;
		int rem = avail - sz - 4;
		freelist.erase(it);
		inverse_freelist.erase({ (char*)ptr-4, avail });
		if (rem > 0)
		{
			void* new_ptr = (char*)ptr + sz;
			freelist.insert({ rem, new_ptr });
			inverse_freelist.insert({ new_ptr, rem });
		}
		return ptr;
	}

	void free(void *ptr)
	{
		ptr = (char*)ptr - 4;
		int sz = *(int*)ptr;

		void* top = ptr;
		void* bottom = (char*)ptr + sz + 4;

		auto it = inverse_freelist.lower_bound({ top, 0 });
		if (it != inverse_freelist.begin())
		{
			it--;
			int t_sz = it->second; void* t_ptr = it->first;
			if ((char*)t_ptr + t_sz == top)
			{
				// This should be merged with current freed mem.
				inverse_freelist.erase(it);
				freelist.erase({ t_sz, t_ptr });
				sz += t_sz;
				ptr = t_ptr;
			}
		}
		it = inverse_freelist.lower_bound({ bottom, 0 });
		if (it != inverse_freelist.end())
		{
			int b_sz = it->second; void* b_ptr = it->first;
			if (b_ptr == bottom)
			{
				// This should be merged with current freed mem.
				inverse_freelist.erase(it);
				freelist.erase({ b_sz, b_ptr });
				sz += b_sz;
			}
		}
		freelist.insert({ sz+4, ptr });
		inverse_freelist.insert({ ptr, sz+4 });
		return;
	}

	void print_freelist()
	{
		for (const auto& [sz, ptr] : freelist)
		{
			std::cout << (char*)ptr-resource << "[" << sz << "] ";
		}
		std::cout << std::endl;
	}
	~MemoryManagement() { delete[] resource; }
};


int main()
{
	MemoryManagement mem_manager;

	void* p = mem_manager.malloc(20);
	void* q = mem_manager.malloc(40);
	void* r = mem_manager.malloc(10);
	mem_manager.print_freelist();
	mem_manager.free(q);
	void* s = mem_manager.malloc(30);
	mem_manager.print_freelist();
	mem_manager.free(s);
	mem_manager.print_freelist();

}