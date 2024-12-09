#include "BookingAgent.h"
#include <fstream>
#include <iostream>
#include <regex>
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
    if (!city.empty()) {
      flights.addVertex(city);
      highSpeedRail.addVertex(city);
    } else {
      throw std::invalid_argument("City name cannot be empty.");
    }
  }

  file.close();
}

// Read travel propositions from a file
void BookingAgent::readTravelPropositions(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Unable to open travel propositions file: " +
                             filename);
  }

  std::string line;
  std::regex regexPattern(
      R"(connection\((\w+),([\w\s]+),([\w\s]+),([\d.]+),(\w+)\))");
  // connection(f, CityA, CityB, 1000, km)

  while (std::getline(file, line)) {
    std::smatch matches;
    if (std::regex_search(line, matches, regexPattern)) {
      std::string mode = matches[1];   // f for flight, r for rail
      std::string cityA = matches[2];  // Origin city
      std::string cityB = matches[3];  // Destination city
      double distanceValue = std::stod(matches[4].str());  // Convert to double
      std::string unit = matches[5];  // Unit of distance (Km, miles)

      // Normalize city names (remove trailing whitespace)
      cityA.erase(cityA.find_last_not_of(" \t\n\r\f\v") + 1);
      cityB.erase(cityB.find_last_not_of(" \t\n\r\f\v") + 1);

      double distanceInKm =
          Measurement(distanceValue, Unit(unit)).toKilometers();

      // Check if cities exist in the graph
      bool cityAExists = flights.contains(cityA) || highSpeedRail.contains(cityA);
      bool cityBExists = flights.contains(cityB) || highSpeedRail.contains(cityB);

      if (!cityAExists || !cityBExists) {
        std::cerr << "Error: One or both cities are missing in the graph: "
                  << cityA << " -> " << cityB << "\n";
        continue;
      }


      TravelProposition proposition(
          cityA, cityB, Measurement(distanceInKm, Unit("km")), mode);

      try {
        if (mode == "flight") { // Mode 'f' for flight
          flights.addEdge(proposition);
        } else if (mode == "r") {  // Mode 'r' for rail
          highSpeedRail.addEdge(proposition);
        } else {
          throw std::invalid_argument("Invalid mode of transport: " + mode);
        }
      } catch (const std::invalid_argument& e) {
        std::cerr << "Error adding edge: " << e.what() << "\n";
      }
    } else {
      std::cerr << "Invalid line format in travel propositions file: " << line
                << "\n";
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
bool BookingAgent::getTrip(const std::string& origin,
                           const std::string& destination) {
  trip.clear();
  totalDistance = Measurement(0, Unit("km"));

  // Try to find the shortest trip using both graphs
  std::vector<TravelProposition> flightPath, railPath;
  Measurement flightDistance(0, Unit("km")), railDistance(0, Unit("km"));

  bool foundFlight = flights.dijkstraShortestPath(origin, destination,
                                                  flightPath, flightDistance);
  bool foundRail = highSpeedRail.dijkstraShortestPath(origin, destination,
                                                      railPath, railDistance);

  if (!foundFlight && !foundRail) {
    std::cerr << "No trip found between " << origin << " and " << destination
              << ".\n";
    return false;
  }

  // Select the shorter trip
  if (foundFlight && (!foundRail || flightDistance.getMagnitude() <
                                        railDistance.getMagnitude())) {
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