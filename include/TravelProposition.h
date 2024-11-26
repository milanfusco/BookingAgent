#ifndef TRAVEL_PROPOSITION_H
#define TRAVEL_PROPOSITION_H

#include <string>
#include "Measurement.h"

class TravelProposition {
 public:

  // Default constructor
  TravelProposition(); 

  // Constructor
  TravelProposition(const std::string& cityA,
                    const std::string& cityB,
                    const Measurement& distance,
                    const std::string& mode);

    // Overload the less than operator
  bool operator<(const TravelProposition& other) const;

  // Getters
  std::string getCityA() const;
  std::string getCityB() const;
  Measurement getDistance() const;
  std::string getTransportMode() const;

  // Display the travel proposition as a string
  std::string toString() const;

 private:
  std::string cityA;          // Origin city
  std::string cityB;          // Destination city
  Measurement distance;       // Distance between cities
  std::string transportMode;  // Mode of transport (e.g., "flight", "rail")
};

#endif  // TRAVEL_PROPOSITION_H
