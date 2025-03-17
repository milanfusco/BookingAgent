# BookingAgent

[![CMake on multiple platforms](https://github.com/milanfusco/BookingAgent/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/milanfusco/BookingAgent/actions/workflows/cmake-multi-platform.yml)

**BookingAgent** is a C++ program designed to calculate the shortest travel path between cities, considering available transportation options like high-speed rail and flights. It uses a graph-based approach to model city connections and applies Dijkstra's algorithm to find the optimal path.

## Features
- Parses city and travel proposition data from external files.
- Supports high-speed rail and flight connections.
- Calculates the shortest path between two cities using Dijkstra's algorithm.
- Outputs travel details, including total distance and mode of transportation.

## Getting Started
### Prerequisites
- **C++ compiler**: ensure you have a C++11 compatible compiler (e.g., ```g++``` or ```clang++```).
- **CMake**: For building the project. (version 3.5 or higher)
### Building the Project
1. Clone the repository and navigate to the project directory:
```
git clone https://github.com/milanfusco/BookingAgent.git
cd BookingAgent
```
2. Build using CMake:
```
mkdir build
cd build
cmake ..
make
```

### Running the Application
Run the main program: 
```
./book <origin_city> <destination_city>
```

## Data Files

### cities.db
This file lists all the cities available for travel, one city per line. Example: 
```
beijing
shanghai
chengdu
...
```
### travel_proposition.db
This file lists all the available travel connections between cities. Each line follows this format:
```
connection(<mode>,<origin>,<destination>,<distance>,<unit>)
```
Where ```<mode>``` is either ```f``` for flights, or ```r``` for high-speed rail. Example:
```
connection(r,shanghai,tokyo,1758,kilometers)
connection(f,cleveland,chengdu,7439,miles)
```

## Testing
The project includes unit tests for each module, located in the /tests/ directory. To run the tests:
1. build the poject and nagivate to the ```build``` directory.
2. Run all tests:
```
ctest
```
3. Or, run a specific test:
```
./GraphTests
```

## Project Structure

- **BookingAgent:**
  - Manages city and travel data.
  - Implements shortest path calculations.
  
- **Graph:**
  - Represents the travel network as vertices (cities) and edges (connections).
  
- **TravelProposition:**
  - Models a connection between two cities with distance and mode of transport.
  
- **Measurement:**
  - Handles distance measurements with unit conversion.
  
- **Unit:**
  - Validates and standardizes units of measurement (e.g., kilometers, miles).

## License
[MIT License](LICENSE)

