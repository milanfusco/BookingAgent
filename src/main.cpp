#include "BookingAgent.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <origin> <destination>\n";
        return 1;  // Exit with an error
    }

    std::string origin = argv[1];
    std::string destination = argv[2];

    BookingAgent agent;

    try {
        // Load cities and travel propositions
        agent.readCities("data/cities.db");
        agent.readTravelPropositions("data/travel_proposition.db");

        // Find trip
        if (agent.getTrip(origin, destination)) {
            std::cout << "Success, trip found! \n";
            agent.printTrip();
        } else {
            std::cout << "No trip found between " << origin << " and " << destination << ".\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;  // Exit with an error 
    }

    return 0;  // Exit successfully
}