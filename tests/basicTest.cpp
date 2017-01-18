#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../src/StandardEvolutionaryAlgorithm.h"
#include "../src/FindMinimumProblem.h"
#include "../src/CartesianPoint.h"
#include "../src/SimpleEvolutionaryAlgorithm.h"
#include "../src/FindMinimumProblemBuilder.h"
#include "../src/EvolutionaryAlgorithmBuilder.h"
#include "../src/Runner.h"

std::unique_ptr<StandardEvolutionaryAlgorithm> setupAlgorithm() {
    std::unique_ptr<FindMinimumProblemBuilder> problemBuilder(new FindMinimumProblemBuilder());
    std::shared_ptr<Problem> problem(problemBuilder->build());
    std::unique_ptr<EvolutionaryAlgorithmBuilder> algorithmBuilder(new EvolutionaryAlgorithmBuilder(EvolutionaryAlgorithmBuilder::STANDARD_ALGORITHM, problem));
    std::unique_ptr<StandardEvolutionaryAlgorithm> algorithm(static_cast<StandardEvolutionaryAlgorithm*>(algorithmBuilder->build()));
    return std::move(algorithm);
}

std::unique_ptr<SimpleEvolutionaryAlgorithm> setupSimpleAlgorithm(unsigned maxTime = 1, double crossoverChance = 0.5) {
    std::unique_ptr<FindMinimumProblemBuilder> problemBuilder(new FindMinimumProblemBuilder());
    std::shared_ptr<Problem> problem(problemBuilder->build());
    std::unique_ptr<EvolutionaryAlgorithmBuilder> algorithmBuilder(new EvolutionaryAlgorithmBuilder(EvolutionaryAlgorithmBuilder::SIMPLE_ALGORITHM, problem));
    std::unique_ptr<SimpleEvolutionaryAlgorithm> algorithm(static_cast<SimpleEvolutionaryAlgorithm*>(
                                                                   algorithmBuilder->withMaxTime(maxTime)->withCrossoverChance(crossoverChance)->build()));
    return std::move(algorithm);
}

TEST_CASE("Algorithm has not empty population") {
    GIVEN("Setup algorithm") {
        std::unique_ptr<StandardEvolutionaryAlgorithm> algorithm = std::move(setupAlgorithm());
        WHEN("Get population from algorithm") {
            auto population = algorithm->getPopulation();
            THEN("Population is not empty") {
                REQUIRE(population.size() > 0);
            }
        }
    }
}

TEST_CASE("Should each point generate 8 points") {
    GIVEN("Setup algorithm") {
        FindMinimumProblemBuilder problemBuilder;
        auto problem(problemBuilder.build());
        std::shared_ptr<IElement> point = std::make_shared<CartesianPoint>(0, 0);
        WHEN("Select next points") {
            auto generatePoints = problem->select(point);
            THEN("Population is not empty") {
                REQUIRE(generatePoints.size() == 8);
            }
        }
    }
}

TEST_CASE("Should reproduce generate 8 points for each point and add population") {
    GIVEN("Setup algorithm") {
        auto algorithm = std::move(setupAlgorithm());
        FindMinimumProblemBuilder problemBuilder;
        auto problem(problemBuilder.build());
        WHEN("Select next points") {
            auto generatePopulation = algorithm->reproduce();
            THEN("Population is not empty") {
                REQUIRE(generatePopulation.size() == 9 * problem->getPopulationSize());
            }
        }
    }
}

TEST_CASE("Should iteration of algorithm create not worse point") {
    GIVEN("Setup algorithm") {
        FindMinimumProblemBuilder problemBuilder;
        auto problem(problemBuilder.build());
        auto algorithm = std::move(setupAlgorithm());
        auto bestPrevPoint = algorithm->getPopulation()[0];
        WHEN("One iteration of algorithm") {
            auto p1 = algorithm->reproduce();
            auto p2 = algorithm->mutate(p1);
            auto p3 = algorithm->crossover(p2);
            algorithm->success(p3);
            THEN("Next population is not worse") {
                auto bestNextPoint = algorithm->getPopulation()[0];
                REQUIRE(problem->rate(bestPrevPoint) <= problem->rate(bestNextPoint));
            }
        }
    }
}

TEST_CASE("Should crossover of 2 points create points between them") {
    GIVEN("Crete both points") {
        double firstPoint = 0;
        double secondPoint = 2;
        double epsilon = std::numeric_limits<double>::epsilon();
        double diff = (secondPoint - firstPoint) / 2;
        std::shared_ptr<IElement> point = std::make_shared<CartesianPoint>(firstPoint, firstPoint);
        std::vector<std::shared_ptr<IElement>> vector{std::make_shared<CartesianPoint>(secondPoint, secondPoint)};
        WHEN("Make crossover") {
            auto genPoint = std::static_pointer_cast<CartesianPoint>(point->crossover(vector));
            THEN("Check if created points is in the middle") {
                REQUIRE(std::abs(genPoint->getX() - diff) < epsilon);
                REQUIRE(std::abs(genPoint->getY() - diff) < epsilon);
            }
        }
    }
}

TEST_CASE("Should succession increment a number of population") {
    GIVEN("Setup algorithm") {
        auto algorithm = std::move(setupAlgorithm());
        auto numberOfPopulation = algorithm->getCurrentPopulation();
        WHEN("Make succession") {
            auto p1 = algorithm->getPopulation();
            algorithm->success(p1);
            THEN("Check if number of population was incremented") {
                auto bestNextPoint = algorithm->getPopulation()[0];
                REQUIRE(numberOfPopulation + 1 == algorithm->getCurrentPopulation());
            }
        }
    }
}

TEST_CASE("Should crossover of 3 points when 2 are equals create points in the middle") {
    GIVEN("Crete points") {
        double firstPoint = 0;
        double secondPoint = 2;
        double epsilon = std::numeric_limits<double>::epsilon();
        double diff = (secondPoint - firstPoint) / 2;
        std::shared_ptr<IElement> point = std::make_shared<CartesianPoint>(firstPoint, firstPoint);
        std::vector<std::shared_ptr<IElement>> vector{std::make_shared<CartesianPoint>(secondPoint, secondPoint),
                                                      std::make_shared<CartesianPoint>(secondPoint, secondPoint)};
        WHEN("Make crossover") {
            auto genPoint = std::static_pointer_cast<CartesianPoint>(point->crossover(vector));
            THEN("Check if created points is in the middle") {
                REQUIRE(std::abs(genPoint->getX() - diff) < epsilon);
                REQUIRE(std::abs(genPoint->getY() - diff) < epsilon);
            }
        }
    }
}

TEST_CASE("Should mutation of point create new one within distribution") {
    GIVEN("Crete points") {
        double distribution = 0.3;
        std::shared_ptr<CartesianPoint> point = std::make_shared<CartesianPoint>(0, 0);
        WHEN("Make crossover") {
            auto genPoint = std::static_pointer_cast<CartesianPoint>(point->mutate());
            THEN("Check if created points is in the middle") {
                REQUIRE(std::abs(genPoint -> getX() - point -> getX()) < distribution);
                REQUIRE(std::abs(genPoint -> getY() - point -> getY()) < distribution);
            }
        }
    }
}

TEST_CASE("Should population after succession be sorted") {
    GIVEN("Setup algorithm") {
        auto algorithm = std::move(setupAlgorithm());
        FindMinimumProblemBuilder problemBuilder;
        auto problem(problemBuilder.build());
        auto rate = 999999.0;
        WHEN("Make iteration") {
            auto p1 = algorithm->reproduce();
            auto p2 = algorithm->mutate(p1);
            auto p3 = algorithm->crossover(p2);
            algorithm->success(p3);
            THEN("Check if sorted by rate of point") {
                for(auto point: algorithm ->getPopulation()) {
                    REQUIRE(problem ->rate(point) <= rate);
                    rate = problem ->rate(point);
                }
            }
        }
    }
}


TEST_CASE("Should algorithm finish after 2 sec") {
    GIVEN("Setup algorithm") {
        auto algorithm = std::shared_ptr<SimpleEvolutionaryAlgorithm>(std::move(setupSimpleAlgorithm(2)));
        auto runner = new Runner(algorithm);
        WHEN("Run algorithm") {
            auto startTime = std::chrono::system_clock::now();
            runner->run();
            THEN("Check if timer counted more than 2 sec") {
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - startTime).count();
                REQUIRE(duration >= 2);
            }
        }
    }
}

TEST_CASE("Should Simple Algorithm mutate all population") {
    GIVEN("Setup algorithm") {
        auto algorithm = std::shared_ptr<SimpleEvolutionaryAlgorithm>(std::move(setupSimpleAlgorithm()));
        auto population = algorithm->getPopulation();
        WHEN("Mutate population") {
            auto mutatedPopulation = algorithm->mutate(population);
            THEN("At least one variable from each element has changed") {
                for (int i = 0; i < population.size(); ++i) {
                    auto element = static_cast<CartesianPoint&>(*(population[i]));
                    auto mutatedElement = static_cast<CartesianPoint&>(*(mutatedPopulation[i]));
                    REQUIRE((element.getX() != mutatedElement.getX() || element.getY() != mutatedElement.getY()));
                }
            }
        }
    }
}

TEST_CASE("Should Simple Algorithm with 0 crossover chance not change any element after crossover") {
    GIVEN("Setup algorithm") {
        auto algorithm = std::shared_ptr<SimpleEvolutionaryAlgorithm>(std::move(setupSimpleAlgorithm(1,0)));
        auto population = algorithm->getPopulation();
        WHEN("Crossover population") {
            auto crossoverPopulation = algorithm->crossover(population);
            THEN("No elements have been changed") {
                for (int i = 0; i < population.size(); ++i) {
                    auto element = static_cast<CartesianPoint&>(*(population[i]));
                    auto mutatedElement = static_cast<CartesianPoint&>(*(crossoverPopulation[i]));
                    REQUIRE((element.getX() == mutatedElement.getX() && element.getY() == mutatedElement.getY()));
                }
            }
        }
    }
}

TEST_CASE("Population after succession should have the same size as original") {
    GIVEN("Setup algorithm") {
        auto algorithm(std::move(setupSimpleAlgorithm()));
        auto population = algorithm->getPopulation();
        WHEN("Get population from algorithm") {
            algorithm->success(population);
            auto succeededPopulation = algorithm->getPopulation();
            THEN("Population is not empty") {
                REQUIRE(population.size() == succeededPopulation.size());
            }
        }
    }
}