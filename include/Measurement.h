#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "Unit.h"
#include <string>

class Measurement {
public:
    Measurement(double magnitude, const Unit& unit);

    // Get the magnitude in kilometers
    double toKilometers() const;

    // Get the magnitude
    double getMagnitude() const;

    // Get the magnitude and unit as a string
    std::string toString() const;

private:
    double magnitude;
    Unit unit;
};

#endif // MEASUREMENT_H
