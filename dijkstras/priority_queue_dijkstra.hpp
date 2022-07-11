#include "../graphs/adj_list_graph.hpp"
#include "../tools/profiler_allocator.hpp"
#include <queue>

using allocT = ProfilerAllocator<std::pair<int, int>>;

template <typename T>
using priority_queue = std::priority_queue<T, std::vector<T, allocT>, std::less<T>>;

int priority_queue_dijkstra(const Graph& graph, ProfilerAllocator<int>& allocator, int& result) {
  allocT alloc = allocator;

  size_t n = graph.size();
  const static int INF = 1e9;

  std::vector<int, ProfilerAllocator<int>> distance(n, INF, alloc);

  size_t start = 0;
  size_t finish = n - 1;
  priority_queue<std::pair<int, int>> q(std::less<std::pair<int, int>>(), alloc);

  q.push({0, start});
  distance[start] = 0;
  while (!q.empty()) {
    auto [inversed_previous_distance, x] = q.top();
    q.pop();

    if (-inversed_previous_distance > distance[x]) continue;

    for (auto y : graph.get_edges(x)) {
      if (distance[y.to] > distance[x] + y.weight) {
        distance[y.to] = distance[x] + y.weight;
        q.push({-distance[y.to], y.to});
      }
    }
  }

  result = distance[finish];
  return distance[finish];
}