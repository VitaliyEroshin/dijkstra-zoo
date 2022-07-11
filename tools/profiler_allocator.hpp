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

#include "profiler_allocator.cpp"