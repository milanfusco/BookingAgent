#include "Measurement.h"
#include <sstream>

// Constructor
Measurement::Measurement(double magnitude, const Unit& unit)
    : magnitude(magnitude), unit(unit) {}

// Convert to kilometers
double Measurement::toKilometers() const {
  return unit.toKilometers(magnitude);
}

// Get the magnitude and unit as a string
double Measurement::getMagnitude() const {
  return magnitude;
}

// Convert to string for display
std::string Measurement::toString() const {
  std::ostringstream oss;
  oss << magnitude << " " << unit.toString();
  return oss.str();
}
