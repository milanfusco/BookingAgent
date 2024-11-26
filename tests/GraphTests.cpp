#include "Graph.h"
#include <cassert>
#include <iostream>

int main() {
    Graph graph;

    // Add vertices
    graph.addVertex("CityA");
    graph.addVertex("CityB");
    graph.addVertex("CityC");
    std::cout << "Vertices added.\n";

    // Add edges
    Measurement distance(100, Unit("km"));
    graph.addEdge(TravelProposition("CityA", "CityB", distance, "flight"));
    graph.addEdge(TravelProposition("CityB", "CityC", distance, "rail"));
    std::cout << "Edges added.\n";

    // Check BFS
    auto path = graph.bfsFindPath("CityA", "CityC");
    assert(!path.empty());
    std::cout << "BFS Test Passed!\n";

    // Check Dijkstra
    std::vector<TravelProposition> dijkstraPath;
    Measurement totalDistance(0, Unit("km"));
    bool found = graph.dijkstraShortestPath("CityA", "CityC", dijkstraPath, totalDistance);
    assert(found);
    assert(abs(totalDistance.toKilometers() - 200) < 1e-6);
    std::cout << "Dijkstra Test Passed!\n";

    std::cout << "All Graph tests passed!\n";
    return 0;
}
