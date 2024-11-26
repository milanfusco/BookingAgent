#include "TravelProposition.h"
#include <cassert>
#include <iostream>

int main() {
    Measurement distance(100, Unit("km"));
    std::cout << "distance weight added.\n";
    TravelProposition tp("CityA", "CityB", distance, "flight");
    std::cout << "TravelProposition created.\n";

    assert(tp.getCityA() == "CityA");
    std::cout << "CityA test passed!\n";
    assert(tp.getCityB() == "CityB");
    std::cout << "CityB test passed!\n";
    assert(tp.getTransportMode() == "flight");
    std::cout << "TransportMode test passed!\n";
    assert(tp.getDistance().toKilometers() == 100);
    std::cout << "Distance test passed!\n";

    std::cout << "All TravelProposition tests passed!\n";
    return 0;
}
