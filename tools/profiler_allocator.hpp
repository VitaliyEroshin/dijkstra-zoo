#pragma once

struct ProfilerAllocatorStats {
    ProfilerAllocatorStats();

    int memory_allocated = 0;
    int memory = 0;
    int max_memory_usage = 0;
    int allocation_calls = 0;
};

namespace ProfilerAllocatorDetail {
    ProfilerAllocatorStats stats;
    ProfilerAllocatorStats getMeasurement();
}

/*
    Modified version of std::allocator, collects information about
    memory consumption. When measurement results are requested, it
    returns stats, collected from previous measurement. 
*/

template <typename T>
class ProfilerAllocator {
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