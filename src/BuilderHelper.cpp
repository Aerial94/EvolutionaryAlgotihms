#include <iostream>
#include "BuilderHelper.h"
#include "CartesianPoint.h"
#include "Runner.h"
#include "EvolutionaryAlgorithmBuilder.h"
#include "FindMinimumProblemBuilder.h"

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

std::shared_ptr<IEvolutionaryAlgorithm> BuilderHelper::createAlgorithm() {
    int algorithmType;
    unsigned populationSize;
    std::shared_ptr<Problem> problem;
    std::shared_ptr<FindMinimumProblemBuilder> problemBuilder(new FindMinimumProblemBuilder());
    std::shared_ptr<EvolutionaryAlgorithmBuilder> algorithmBuilder;

    unsigned tournamentSize;
    double crossoverChance;
    size_t crossoverPoints;
    size_t mutationSize;
    std::shared_ptr<IEvolutionaryAlgorithm> algorithm;
    std::cout << "Choose algorithm type: [1] SimpleEvolutionaryAlgorithm [2] StandardEvolutionaryAlgorithm: [0] Exit" << std::endl;
    algorithmType = valueFromStream<int>();
    if(algorithmType == 0) {
        return nullptr;
    }
    std::cout << "Set population size: " << std::endl;
    populationSize = valueFromStream<unsigned>();
    problem = std::shared_ptr<Problem>(problemBuilder->withPopulationSize(populationSize)->build());
    if (algorithmType == 1) {
        std::cout << "Set tournament size: " << std::endl;
        tournamentSize = valueFromStream<unsigned>();
        std::cout << "Set crossover chance: " << std::endl;
        crossoverChance = valueFromStream<double>();
        algorithmBuilder = std::shared_ptr<EvolutionaryAlgorithmBuilder>(new EvolutionaryAlgorithmBuilder(EvolutionaryAlgorithmBuilder::SIMPLE_ALGORITHM, problem));
        algorithm = std::shared_ptr<IEvolutionaryAlgorithm>(algorithmBuilder->withTournamentSize(tournamentSize)->withCrossoverChance(crossoverChance)->build());
    } else if (algorithmType == 2) {
        std::cout << "Set crossover points: " << std::endl;
        crossoverPoints = valueFromStream<size_t>();
        std::cout << "Set mutation size : " << std::endl;
        mutationSize = valueFromStream<size_t>();
        algorithmBuilder = std::shared_ptr<EvolutionaryAlgorithmBuilder>(new EvolutionaryAlgorithmBuilder(EvolutionaryAlgorithmBuilder::STANDARD_ALGORITHM, problem));
        algorithm = std::shared_ptr<IEvolutionaryAlgorithm>(algorithmBuilder->withCrossoverPoints(crossoverPoints)->withMutationSize(mutationSize)->build());
    }
    return algorithm;
}


