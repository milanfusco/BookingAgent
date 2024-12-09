#include "Unit.h"
#include <stdexcept>

// Conversion factors (unit -> kilometers)
const std::unordered_map<std::string, double> Unit::conversionFactors = {
    {"km", 1.0},         // Kilometers
    {"kilometers", 1.0}, // Kilometers
    {"miles", 1.60934},  // Miles to kilometers
    {"meters", 0.001},   // Meters to kilometers
    {"feet", 0.0003048}  // Feet to kilometers
};

// Constructor
Unit::Unit(const std::string& name) : name(name) {
  if (!isValidUnit(name)) {
    throw std::invalid_argument("Invalid unit: " + name);
  }
}

// Check if the unit is valid
bool Unit::isValidUnit(const std::string& name) {
  return conversionFactors.find(name) != conversionFactors.end();
}

// Convert to kilometers
double Unit::toKilometers(double magnitude) const {
  if (!isValidUnit(name)) {
    throw std::invalid_argument("Invalid unit: " + name);
  }
  return magnitude * conversionFactors.at(name);
}

// Get the unit as a string
std::string Unit::toString() const {
  return name;
}
