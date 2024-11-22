cmake_minimum_required(VERSION 3.0.0)
project(new_project VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(./include)

file(GLOB TARGET_SRC "./src/*.cpp" )

add_executable(main ${TARGET_SRC})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
