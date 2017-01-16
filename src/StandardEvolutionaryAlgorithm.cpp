#include "StandardEvolutionaryAlgorithm.h"
#include "FindMinimumProblem.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>

StandardEvolutionaryAlgorithm::StandardEvolutionaryAlgorithm(
        std::shared_ptr<Problem> problem, size_t crossoverPoints, size_t mutationSize, unsigned numberOfPopulation)
        : IEvolutionaryAlgorithm(problem), crossoverPoints(crossoverPoints), mutationSize(mutationSize), numberOfPopulation(numberOfPopulation) {
    currentPopulation = 0;
    population = problem->generate();
    std::sort(population.begin(), population.end(),
              [&](std::shared_ptr<IElement> &a, std::shared_ptr<IElement> &b) -> bool {
                  return problem->rate(a) > problem->rate(b);
              });
    theWorstElements = std::vector<std::shared_ptr<IElement>>(population.end() - std::min(population.size(), crossoverPoints), population.end());
    maxElement = population[0];
}


std::vector<std::shared_ptr<IElement>>
StandardEvolutionaryAlgorithm::mutate(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    unsigned seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(tempPopulation.begin(), tempPopulation.end(), std::default_random_engine(seed));
    std::vector<std::shared_ptr<IElement>> mutatedPopulation;
    int i = 0;

    for (std::shared_ptr<IElement> &element: tempPopulation) {
        if (++i > mutationSize) {
            mutatedPopulation.push_back(element);
        } else {
            mutatedPopulation.push_back(element->mutate());
        }
    }
    return mutatedPopulation;
}

std::vector<std::shared_ptr<IElement>> StandardEvolutionaryAlgorithm::reproduce() {
    std::vector<std::shared_ptr<IElement>> population = std::move(getPopulation());
    std::vector<std::shared_ptr<IElement>> newPopulation;
    for (std::shared_ptr<IElement> &element: population) {
        std::vector<std::shared_ptr<IElement>> neighbours = problem->select(element);
        newPopulation.insert(newPopulation.end(), neighbours.begin(), neighbours.end());
        newPopulation.push_back(element);
    }
    return newPopulation;
}

void StandardEvolutionaryAlgorithm::success(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    std::sort(tempPopulation.begin(), tempPopulation.end(),
              [&](std::shared_ptr<IElement> &a, std::shared_ptr<IElement> &b) -> bool {
                  return problem->rate(a) > problem->rate(b);
              });
    population = std::vector<std::shared_ptr<IElement>>(tempPopulation.begin(),
                                                        tempPopulation.begin() +
                                                        std::min(tempPopulation.size(), problem->getPopulationSize()));
    theWorstElements = std::vector<std::shared_ptr<IElement>>(
            tempPopulation.end() - std::min(tempPopulation.size(), crossoverPoints),
            tempPopulation.end());
    currentPopulation += 1;
}

bool StandardEvolutionaryAlgorithm::finish() {
    return currentPopulation > numberOfPopulation;
}

std::vector<std::shared_ptr<IElement>>
StandardEvolutionaryAlgorithm::crossover(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    std::vector<std::shared_ptr<IElement>> newPopulation (theWorstElements.begin(), theWorstElements.end());
    std::transform(newPopulation.begin(), newPopulation.end(), newPopulation.begin(), [this](std::shared_ptr<IElement> &a) {
        std::vector<std::shared_ptr<IElement>> vector {maxElement};
        return a->crossover(vector);
    });
    newPopulation.insert(newPopulation.end(), tempPopulation.begin(), tempPopulation.end());

    return newPopulation;
}
