#include "testing/measurements.hpp"
#include "graphs/adj_list_graph.hpp"
#include "dijkstras/priority_queue_dijkstra.hpp"

int main() {
    auto g = generate_unoriented_graph(23901, 23901 * 20, 572);
    run_test(10, g, priority_queue_dijkstra);
}