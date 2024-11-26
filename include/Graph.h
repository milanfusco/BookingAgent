#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include "TravelProposition.h"

class Graph {
 public:
  // Constructor
  Graph();

  // Add a vertex (city)
  void addVertex(const std::string& city);

  // Add an edge (travel proposition)
  void addEdge(const TravelProposition& proposition);

  // BFS to find any path between two vertices
  std::stack<TravelProposition> bfsFindPath(const std::string& start, const std::string& end);

  // Dijkstra's Algorithm to find the shortest path
  bool dijkstraShortestPath(const std::string& start, const std::string& end,
                            std::vector<TravelProposition>& path, Measurement& distance);

  // Display the graph
  void displayGraph() const;

 private:
  std::set<std::string> vertices;                        // Set of cities (vertices)
  std::set<TravelProposition> edges;                     // Set of travel propositions (edges)
  std::unordered_map<std::string, std::vector<TravelProposition>> adjacencyList;  // Adjacency list

  // Helper to build adjacency list
  void updateAdjacencyList(const TravelProposition& proposition);
};

#endif  // GRAPH_H
