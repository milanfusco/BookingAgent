#include "BookingAgent.h"
#include <cassert>
#include <iostream>

int main() {
    BookingAgent agent;

    // Create test cities and travel propositions
    agent.readCities("../data/cities.db");
    std::cout << "Cities added.\n";
    agent.readTravelPropositions("../data/travel_proposition.db");
    std::cout << "Travel propositions added.\n";

    // Test trip finding
    assert(agent.getTrip("cleveland", "algiers"));
    agent.printTrip();

    std::cout << "BookingAgent tests passed.\n";
    return 0;
}
