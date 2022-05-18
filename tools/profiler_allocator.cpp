#include "profiler_allocator.hpp"

using namespace ProfilerAllocatorDetail;

template <typename T>
T* ProfilerAllocator<T>::allocate(size_t n) {
    stats.memory_allocated += n * sizeof(T);
    stats.memory += n * sizeof(T);
    stats.max_memory_usage = std::max(stats.memory, stats.max_memory_usage);
    ++stats.allocation_calls;

    return reinterpret_cast<T*>(new int8_t[n * sizeof(T)]); 
}

template <typename T>
void ProfilerAllocator<T>::deallocate(const T* ptr, size_t n) {
    stats.memory -= n * sizeof(T);
    ::operator delete(const_cast<T*>(ptr));
}

ProfilerAllocatorStats::ProfilerAllocatorStats()
    : memory_allocated(0)
    , memory(0)
    , max_memory_usage(0)
    , allocation_calls(0)
{}

ProfilerAllocatorStats getMeasurement() {
    ProfilerAllocatorStats copy;
    std::swap(copy, stats);
    return copy;
}