#include "Graph.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <limits>

// Constructor
Graph::Graph() {}

// Add a vertex
void Graph::addVertex(const std::string& city) {
  vertices.insert(city);
  adjacencyList[city];  // Ensure city exists in adjacency list
}

// Add an edge
void Graph::addEdge(const TravelProposition& proposition) {
  const std::string& cityA = proposition.getCityA();
  const std::string& cityB = proposition.getCityB();

  if (vertices.find(cityA) == vertices.end() ||
      vertices.find(cityB) == vertices.end()) {
    throw std::invalid_argument(
        "One or both cities are not in the graph: " + cityA + " -> " + cityB);
  }

  edges.insert(proposition);
  updateAdjacencyList(proposition);
}

// Check if a vertex exists in the graph
bool Graph::contains(const std::string& city) const {
  return vertices.find(city) != vertices.end();
}

// Update adjacency list
void Graph::updateAdjacencyList(const TravelProposition& proposition) {
  adjacencyList[proposition.getCityA()].push_back(proposition);
}

// Display the graph
void Graph::displayGraph() const {
  std::cout << "Vertices:\n";
  for (const auto& vertex : vertices) {
    std::cout << "  " << vertex << "\n";
  }
  std::cout << "\nEdges:\n";
  for (const auto& edge : edges) {
    std::cout << "  " << edge.toString() << "\n";
  }
}

// Dijkstra's Algorithm to find the shortest path
bool Graph::dijkstraShortestPath(const std::string& start,
                                 const std::string& end,
                                 std::vector<TravelProposition>& path,
                                 Measurement& totalDistance) {
  if (vertices.find(start) == vertices.end() ||
      vertices.find(end) == vertices.end()) {
    throw std::invalid_argument("One or both cities are not in the graph.");
  }

  std::unordered_map<std::string, double>
      distances;  // Distance from start to each city
  std::unordered_map<std::string, TravelProposition>
      previousEdge;  // Tracks incoming edges
  std::priority_queue<std::pair<double, std::string>,
                      std::vector<std::pair<double, std::string>>,
                      std::greater<std::pair<double, std::string>>>
      pq;  // Min-heap based on distance

  for (const auto& city : vertices) {
    distances[city] = std::numeric_limits<double>::infinity();
  }
  distances[start] = 0;
  pq.emplace(0, start);

  while (!pq.empty()) {
    std::pair<double, std::string> top = pq.top();
    double currentDistance = top.first;
    std::string currentCity = top.second;
    pq.pop();

    if (currentCity == end) {
      // Build the path using previousEdge map
      path.clear();
      totalDistance = Measurement(currentDistance, Unit("km"));
      while (currentCity != start) {
        const TravelProposition& edge = previousEdge[currentCity];
        path.insert(path.begin(), edge);
        currentCity = edge.getCityA();
      }
      return true;
    }

    for (const auto& edge : adjacencyList[currentCity]) {
      const std::string& neighbor = edge.getCityB();
      double edgeDistance = edge.getDistance().getMagnitude();

      if (distances[currentCity] + edgeDistance < distances[neighbor]) {
        distances[neighbor] = distances[currentCity] + edgeDistance;
        previousEdge[neighbor] = edge;
        pq.emplace(distances[neighbor], neighbor);
      }
    }
  }

  return false;  // No path found
}
