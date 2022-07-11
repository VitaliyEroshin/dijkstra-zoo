#include "../tools/profiler_allocator.hpp"
#include "../tools/time_profiler.hpp"
#include "../graphs/adj_list_graph.hpp"
#include <iostream>

template <typename Fn>
int run_test(int probes, const Graph& graph, Fn&& f) {
    int result;
    ProfilerAllocator<int> allocator;
    int compute_time = duration(probes, f, graph, allocator, result);
    std::cout << "  time: " << compute_time << "ms." << std::endl;
    std::cout << "  alloc calls: " << allocator.allocation_calls << std::endl;
    std::cout << "  max mem usage: " << allocator.max_memory_usage << std::endl;
    std::cout << "  mem allocated: " << allocator.memory_allocated << std::endl;

    return result;
}