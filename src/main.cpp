#include <memory>
#include <iostream>
#include "Problem.h"
#include "IEvolutionaryAlgorithm.h"
#include "StandardEvolutionaryAlgorithm.h"
#include "Runner.h"
#include "FindMinimumProblem.h"
#include "SimpleEvolutionaryAlgorithm.h"
#include "FindMinimumProblemBuilder.h"
#include "EvolutionaryAlgorithmBuilder.h"
#include "CartesianPoint.h"

#define CATCH_CONFIG_MAIN

template <typename T>
T valueFromStream() {
    T value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Incorrect entry. Try again: ";
    }
    return value;
}

int main(int argc, char* argv[])  {
    int algorithmType;
    unsigned populationSize;
    std::shared_ptr<Problem> problem;
    std::unique_ptr<FindMinimumProblemBuilder> problemBuilder(new FindMinimumProblemBuilder());
    std::shared_ptr<EvolutionaryAlgorithmBuilder> algorithmBuilder;

    unsigned tournamentSize;
    double crossoverChance;
    size_t crossoverPoints;
    size_t mutationSize;
    std::unique_ptr<IEvolutionaryAlgorithm> algorithm;


    while (1) {
        std::cout << "Choose algorithm type: [1] SimpleEvolutionaryAlgorithm [2] StandardEvolutionaryAlgorithm: [0] Exit" << std::endl;
        algorithmType = valueFromStream<int>();
        std::cout << "Set population size: " << std::endl;
        populationSize = valueFromStream<unsigned>();
        problem = std::shared_ptr<Problem>(problemBuilder->withPopulationSize(populationSize)->build());
        if (algorithmType == 1) {
            std::cout << "Set tournament size: " << std::endl;
            tournamentSize = valueFromStream<unsigned>();
            std::cout << "Set crossover chance: " << std::endl;
            crossoverChance = valueFromStream<double>();
            algorithmBuilder = std::shared_ptr<EvolutionaryAlgorithmBuilder>(new EvolutionaryAlgorithmBuilder(EvolutionaryAlgorithmBuilder::SIMPLE_ALGORITHM, problem));
            algorithm = std::unique_ptr<IEvolutionaryAlgorithm>(algorithmBuilder->withTournamentSize(tournamentSize)->withCrossoverChance(crossoverChance)->build());
        } else if (algorithmType == 2) {
            std::cout << "Set crossover points: " << std::endl;
            crossoverPoints = valueFromStream<size_t>();
            std::cout << "Set mutation size : " << std::endl;
            mutationSize = valueFromStream<size_t>();
            algorithmBuilder = std::shared_ptr<EvolutionaryAlgorithmBuilder>(new EvolutionaryAlgorithmBuilder(EvolutionaryAlgorithmBuilder::STANDARD_ALGORITHM, problem));
            algorithm = std::unique_ptr<IEvolutionaryAlgorithm>(algorithmBuilder->withCrossoverPoints(crossoverPoints)->withMutationSize(mutationSize)->build());
        } else if (algorithmType == 0) {
            break;
        }

        if (algorithm) {
            Runner runner(std::move(algorithm));
            auto population = runner.run();
            std::cout << "Current algorithm population: " << std::endl;
            for (auto element: population) {
                CartesianPoint point = static_cast<CartesianPoint&>(*element);
                std::cout << point << std::endl;
            }
            std::cout << std::endl << "End of population.";
        }
    }





//    std::shared_ptr<Problem> problem(new FindMinimumProblem());
//    std::unique_ptr<IEvolutionaryAlgorithm> algorithm(new StandardEvolutionaryAlgorithm(problem));
////    std::unique_ptr<IEvolutionaryAlgorithm> algorithm(new SimpleEvolutionaryAlgorithm(problem));
//    Runner runner(std::move(algorithm));
//    runner.run();
    return 0;
}

