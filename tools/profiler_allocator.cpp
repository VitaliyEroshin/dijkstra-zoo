#include "profiler_allocator.hpp"

int ProfilerAllocatorStats::memory_allocated = 0;
int ProfilerAllocatorStats::memory = 0;
int ProfilerAllocatorStats::max_memory_usage = 0;
int ProfilerAllocatorStats::allocation_calls = 0;

template <typename T>
T* ProfilerAllocator<T>::allocate(size_t n) {
    memory_allocated += n * sizeof(T);
    memory += n * sizeof(T);
    max_memory_usage = std::max(memory, max_memory_usage);
    ++allocation_calls;

    return reinterpret_cast<T*>(new uint8_t[n * sizeof(T)]); 
}

template <typename T>
void ProfilerAllocator<T>::deallocate(const T* ptr, size_t n) {
    memory -= n * sizeof(T);
    ::operator delete(const_cast<T*>(ptr));
}