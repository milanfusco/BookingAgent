#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <unordered_map>

class Unit {
public:
    explicit Unit(const std::string& name);

    // Get the conversion factor to kilometers
    double toKilometers(double magnitude) const;

    // Check if the unit is valid
    static bool isValidUnit(const std::string& name);

    // Get the unit as a string
    std::string toString() const;

private:
    std::string name;

    // Conversion factors to kilometers
    static const std::unordered_map<std::string, double> conversionFactors;
};

#endif // UNIT_H
