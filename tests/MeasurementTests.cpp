#include "Measurement.h"
#include <cassert>
#include <iostream>

int main() {
    Unit kilometers("km");
    std::cout << "KM unit created.\n";
    Measurement m1(100, kilometers);
    std::cout << "Measurement created.\n";

    assert(m1.getMagnitude() == 100);
    std::cout << "Magnitude test passed!\n";
    assert(m1.toKilometers() == 100);
    std::cout << "toKilometers test passed!\n";

    Unit miles("miles");
    std::cout << "Miles unit created.\n";
    Measurement m2(1, miles);
    std::cout << "Measurement created.\n";
    assert(abs(m2.toKilometers() - 1.60934) < 1e-6);
    std::cout << "toKilometers test passed!\n";

    std::cout << "All Measurement tests passed!\n";
    return 0;
}
