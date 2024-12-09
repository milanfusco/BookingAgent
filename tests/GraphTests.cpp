#include "Graph.h"
#include <cassert>
#include <iostream>

int main() {
    Graph graph;

    // Add vertices
    graph.addVertex("bejing");
    graph.addVertex("shanghai");
    graph.addVertex("tokyo");
    std::cout << "Vertices added.\n";

    // Add edges
    Measurement distance1(1758, Unit("km"));
    graph.addEdge(TravelProposition("shanghai", "tokyo", distance1, "rail"));

    Measurement distance2(1214, Unit("km"));
    graph.addEdge(TravelProposition("bejing", "shanghai", distance2, "rail"));

    std::cout << "Edges added.\n";
    std::cout << "Graph: \n";
    graph.displayGraph();

    // Check Dijkstra
    std::vector<TravelProposition> dijkstraPath;
    Measurement totalDistance(0, Unit("km"));
    bool found = graph.dijkstraShortestPath("bejing", "tokyo", dijkstraPath, totalDistance);
    if (!found) {
        std::cerr << "Dijkstra's algorithm failed to find a path from bejing to tokyo.\n";
    } else {
        std::cout << "\nPath found with total distance: " << totalDistance.toKilometers() << " km\n";
        for (const auto& step : dijkstraPath) {
            std::cout << step.toString() << "\n";
        }
    }

    // Assert path was found
    assert(found);
    std::cout << "Dijkstra Test Passed!\n";

    std::cout << "All Graph tests passed!\n";
    return 0;
}
