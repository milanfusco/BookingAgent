cmake_minimum_required(VERSION 3.5.0)
project(BookingAgent VERSION 0.1.0)

# Include the CTest module for testing
include(CTest)
enable_testing()

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directory for header files
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

# Create a library from the source files and add it to the project
add_library(BookingAgentLib STATIC ${LIBRARY_SRC})

# Create the main executable and link the library
add_executable(book ${MAIN_SRC})
target_link_libraries(book PRIVATE BookingAgentLib)

# Custom target to copy data files to the build directory
add_custom_target(copy_data ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
)

# Ensure the main executable depends on the data
add_dependencies(book copy_data)


# Define the test source files
file(GLOB TESTS_SRC "./tests/*.cpp")

# Create test executables and link the library
foreach(TEST_SRC ${TESTS_SRC})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)  # Extract the test name
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} PRIVATE BookingAgentLib)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# CPack configuration 
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)