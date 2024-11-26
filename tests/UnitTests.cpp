#include "Unit.h"
#include <cassert>
#include <iostream>

int main() {
    // Test valid conversions
    Unit kilometers("km");
    assert(kilometers.toKilometers(1) == 1.0);
    std::cout << "Kilometer test passed!\n";

    Unit miles("miles");
    assert(abs(miles.toKilometers(1) - 1.60934) < 1e-6);
    std::cout << "Mile test passed!\n";

    Unit meters("meters");
    assert(abs(meters.toKilometers(1000) - 1.0) < 1e-6);
    std::cout << "Meter test passed!\n";

    Unit feet("feet");
    assert(abs(feet.toKilometers(3280.84) - 1.0) < 1e-6);
    std::cout << "Feet test passed!\n";

    // Test invalid unit
    try {
        Unit invalid("invalid");
        assert(false);  // This line should never be reached
    } catch (const std::invalid_argument&) {
        // Expected exception
    }
    std::cout << "Invalid unit test passed!\n";

    std::cout << "All unit tests passed!\n";
    return 0;
}