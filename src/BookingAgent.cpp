#include "BookingAgent.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Constructor
BookingAgent::BookingAgent() : totalDistance(0, Unit("km")) {}

// Read cities from a file
void BookingAgent::readCities(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Unable to open cities file: " + filename);
  }

  std::string city;
  while (std::getline(file, city)) {
    flights.addVertex(city);
    highSpeedRail.addVertex(city);
  }

  file.close();
}

// Read travel propositions from a file
void BookingAgent::readTravelPropositions(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Unable to open travel propositions file: " + filename);
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream ss(line);
    std::string cityA, cityB, mode;
    double distanceValue;
    ss >> cityA >> cityB >> distanceValue >> mode;

    TravelProposition proposition(
        cityA, cityB, Measurement(distanceValue, Unit("km")), mode);

    if (mode == "flight") {
      flights.addEdge(proposition);
    } else if (mode == "rail") {
      highSpeedRail.addEdge(proposition);
    } else {
      throw std::invalid_argument("Invalid mode of transport: " + mode);
    }
  }

  file.close();
}

// Helper to select the graph based on the mode of transport
Graph& BookingAgent::selectGraph(const std::string& mode) {
  if (mode == "flight") {
    return flights;
  } else if (mode == "rail") {
    return highSpeedRail;
  } else {
    throw std::invalid_argument("Invalid mode of transport: " + mode);
  }
}

// Find a trip between origin and destination
bool BookingAgent::getTrip(const std::string& origin, const std::string& destination) {
  trip.clear();
  totalDistance = Measurement(0, Unit("km"));

  // Try to find the shortest trip using both graphs
  std::vector<TravelProposition> flightPath, railPath;
  Measurement flightDistance(0, Unit("km")), railDistance(0, Unit("km"));

  bool foundFlight = flights.dijkstraShortestPath(origin, destination, flightPath, flightDistance);
  bool foundRail = highSpeedRail.dijkstraShortestPath(origin, destination, railPath, railDistance);

  if (!foundFlight && !foundRail) {
    std::cerr << "No trip found between " << origin << " and " << destination << ".\n";
    return false;
  }

  // Select the shorter trip
  if (foundFlight && (!foundRail || flightDistance.getMagnitude() < railDistance.getMagnitude())) {
    trip = flightPath;
    totalDistance = flightDistance;
  } else {
    trip = railPath;
    totalDistance = railDistance;
  }

  return true;
}

// Print the trip details
void BookingAgent::printTrip() const {
  if (trip.empty()) {
    std::cout << "No trip available.\n";
    return;
  }

  std::cout << "\nTrip Details:\n";
  for (const auto& proposition : trip) {
    std::cout << proposition.toString() << "\n";
  }
  std::cout << "Total Distance: " << totalDistance.toString() << "\n";
}

// Display graphs
void BookingAgent::displayGraphs() const {
  std::cout << "Flight Graph:\n";
  flights.displayGraph();
  
  std::cout << "High-Speed Rail Graph:\n";
  highSpeedRail.displayGraph();
}