#include "BookingAgent.h"
#include <cassert>
#include <iostream>

int main() {
    BookingAgent agent;

    // Create test cities and travel propositions
    agent.readCities("/Users/milanfusco/Documents/repositories/BookingAgent/tests/test_cities.txt");  // Ensure this file exists with valid city names
    agent.readTravelPropositions("/Users/milanfusco/Documents/repositories/BookingAgent/tests/test_travel.txt");  // Ensure this file exists with valid propositions
    agent.displayGraphs();

    // Test trip finding
    assert(agent.getTrip("CityA", "CityC"));
    agent.printTrip();

    std::cout << "BookingAgent tests passed.\n";
    return 0;
}
