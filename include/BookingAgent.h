#ifndef BOOKING_AGENT_H
#define BOOKING_AGENT_H

#include "Graph.h"
#include <string>
#include <vector>

class BookingAgent {
 public:
  // Constructor
  BookingAgent();

  // Read cities from a file
  void readCities(const std::string& filename);

  // Read travel propositions from a file
  void readTravelPropositions(const std::string& filename);

  // Find a trip between origin and destination
  bool getTrip(const std::string& origin, const std::string& destination);

  // Print the trip details
  void printTrip() const;

  // Display graphs
  void displayGraphs() const;

 private:
  Graph flights;         // Graph for flight connections
  Graph highSpeedRail;   // Graph for high-speed rail connections
  std::vector<TravelProposition> trip;  // Stores the selected trip
  Measurement totalDistance;  // Stores the total distance of the trip

  // Helper to choose the graph based on a mode of transport
  Graph& selectGraph(const std::string& mode);
};

#endif  // BOOKING_AGENT_H
