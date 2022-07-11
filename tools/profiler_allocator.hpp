#pragma once
#include <cstddef> // size_t
#include <stdint.h> // uint8_t
#include <algorithm> // std::max

struct ProfilerAllocatorStats {
  static int memory_allocated;
  static int memory;
  static int max_memory_usage;
  static int allocation_calls;
};

/*
    Modified version of std::allocator, collects information about
    memory consumption. When measurement results are requested, it
    returns stats, collected from previous measurement. 
*/

template <typename T>
class ProfilerAllocator : public ProfilerAllocatorStats {
public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  template <typename U>
  struct rebind {
    typedef ProfilerAllocator<U> other;
  };

  ProfilerAllocator() {}

  template <typename U>
  ProfilerAllocator<T>(const ProfilerAllocator<U>&) {}

  T* allocate(size_t n);
  
  void deallocate(const T* ptr, size_t n);
};

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