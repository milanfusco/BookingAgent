#include "TravelProposition.h"
#include <sstream>

// Default constructor
TravelProposition::TravelProposition()
    : cityA(""), cityB(""), distance(0, Unit("km")), transportMode("") {}

// Constructor
TravelProposition::TravelProposition(const std::string& cityA,
                                     const std::string& cityB,
                                     const Measurement& distance,
                                     const std::string& mode)
    : cityA(cityA), cityB(cityB), distance(distance), transportMode(mode) {}


// Overload the less than operator
bool TravelProposition::operator<(const TravelProposition& other) const {
  if (cityA != other.cityA)
    return cityA < other.cityA;
  if (cityB != other.cityB)
    return cityB < other.cityB;
  if (transportMode != other.transportMode)
    return transportMode < other.transportMode;
  return distance.toKilometers() < other.distance.toKilometers();
}

// Getters
std::string TravelProposition::getCityA() const {
  return cityA;
}

std::string TravelProposition::getCityB() const {
  return cityB;
}

Measurement TravelProposition::getDistance() const {
  return distance;
}

std::string TravelProposition::getTransportMode() const {
  return transportMode;
}

// Display the travel proposition as a string
std::string TravelProposition::toString() const {
  std::ostringstream oss;
  oss << "From: " << cityA << ", To: " << cityB
      << ", Distance: " << distance.toKilometers() << " km"
      << ", Mode: " << transportMode;
  return oss.str();
}
