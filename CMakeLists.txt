cmake_minimum_required(VERSION 3.5.0)
project(new_project VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(./include)

# Define the library source files
file(GLOB LIBRARY_SRC
    "./src/BookingAgent.cpp"
    "./src/Graph.cpp"
    "./src/Measurement.cpp"
    "./src/TravelProposition.cpp"
    "./src/Unit.cpp"
)

# Define the main executable source file
set(MAIN_SRC "./src/main.cpp")

# Create a library from the source files (shared or static)
add_library(BookingAgentLib STATIC ${LIBRARY_SRC})

# Create the main executable and link the library
add_executable(main ${MAIN_SRC})
target_link_libraries(main PRIVATE BookingAgentLib)

# Define the test source files
file(GLOB TESTS_SRC "./tests/*.cpp")

# Create test executables and link the library
foreach(TEST_SRC ${TESTS_SRC})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)  # Extract the test name
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} PRIVATE BookingAgentLib)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# CPack configuration (optional)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)