cmake_minimum_required(VERSION 3.4)
project(EvolutionaryAlgotihms)

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(Test basicTest.cpp ../src/StandardEvolutionaryAlgorithm.cpp ../src/StandardEvolutionaryAlgorithm.h ../src/FindMinimumProblem.h
        ../src/FindMinimumProblem.cpp ../src/CartesianPoint.cpp ../src/CartesianPoint.h)
target_link_libraries(Test Catch)

enable_testing()
add_test(NAME factorial COMMAND basicTest.cpp)