#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/StandardEvolutionaryAlgorithm.h"
#include "../src/FindMinimumProblem.h"

std::unique_ptr<IEvolutionaryAlgorithm> setupAlgorithm() {
    std::shared_ptr<Problem> problem(new FindMinimumProblem());
    std::unique_ptr<IEvolutionaryAlgorithm> algorithm(new StandardEvolutionaryAlgorithm(problem));
    return std::move(algorithm);
}


TEST_CASE( "Algorithm has not empty population") {
    GIVEN("Setup algorithm") {
        std::unique_ptr<IEvolutionaryAlgorithm> algorithm = std::move(setupAlgorithm());
        WHEN("Get population from algorithm") {
            auto population = algorithm->getPopulation();
            THEN("Population is not empty") {
                REQUIRE(population.size() > 0);
            }
        }
    }
}
