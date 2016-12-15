cmake_minimum_required(VERSION 3.4)
project(EvolutionaryAlgotihms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
     src/main.cpp src/Problem.h src/IElement.cpp src/IElement.h src/IEvolutionaryAlgorithm.h src/Runner.cpp src/Runner.h src/StandardEvolutionaryAlgorithm.cpp src/StandardEvolutionaryAlgorithm.h)

add_executable(EvolutionaryAlgotihms ${SOURCE_FILES} src/main.cpp)

add_subdirectory(tests)


