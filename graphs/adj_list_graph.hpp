#pragma once
#include <cstddef> // size_t
#include <vector>
#include <algorithm> // std::swap
#include <set>
#include <utility>

struct Edge {
  size_t to;
  int weight;
};

class Graph {
public:
  Graph(size_t n)
  { graph.resize(n); }

  void add_edge(size_t from, Edge edge, bool oriented = false) {
    graph[from].push_back(edge);
    if (!oriented) {
      std::swap(from, edge.to);
      graph[from].push_back(edge);
    }
  }

  const std::vector<Edge>& get_edges(size_t from) const 
  { return graph[from]; }

  size_t size() const 
  { return graph.size(); }

private:
  std::vector<std::vector<Edge>> graph;
};

std::pair<size_t, size_t> generate_edge(size_t size) {
  size_t x = rand() % size;
  size_t y = rand() % size;
  if (y < x)
    std::swap(x, y);

  return {x, y}; 
}

Graph generate_unoriented_graph(size_t size, size_t edges, size_t max_distance) {
  std::set<std::pair<size_t, size_t>> added;
  Graph graph(size);
  for (size_t i = 0; i < edges; ++i) {
    auto edge = generate_edge(size);
    while (added.count(edge) || edge.first == edge.second) {
      edge = generate_edge(size);
    }

    int weight = rand() % max_distance + 1;
    graph.add_edge(edge.first, {edge.second, weight});
    added.insert(edge);
  }
  return graph;
}