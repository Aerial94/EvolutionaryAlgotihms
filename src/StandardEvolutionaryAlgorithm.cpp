#include "StandardEvolutionaryAlgorithm.h"
#include "FindMinimumProblem.h"
#include <random>
#include <chrono>
#include <algorithm>

StandardEvolutionaryAlgorithm::StandardEvolutionaryAlgorithm(std::unique_ptr<Problem> problem) {
    currentPopulation = 0;
    problem = std::move(problem);
    population = problem->generate();
    theWorstElements = std::vector<std::shared_ptr<IElement>>(population.end() - std::min(population.size(), CROSSOVER_POINTS),
                                                   population.end());
    maxElement = population[0];
}


std::vector<std::shared_ptr<IElement>>
StandardEvolutionaryAlgorithm::mutate(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    unsigned seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(tempPopulation.begin(), tempPopulation.end(), std::default_random_engine(seed));
    std::vector<std::shared_ptr<IElement>> mutatedPopulation;
    int i = 0;

    for (std::shared_ptr<IElement> &element: tempPopulation) {
        if (++i > MUTATION_SIZE) {
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
                                                        std::min(tempPopulation.size(), FindMinimumProblem::POPULATION_SIZE));
    theWorstElements = std::vector<std::shared_ptr<IElement>>(
            tempPopulation.end() - std::min(tempPopulation.size(), CROSSOVER_POINTS),
            tempPopulation.end());
    currentPopulation += 1;
}

bool StandardEvolutionaryAlgorithm::finish() {
    return currentPopulation > NUMBER_OF_POPULATION;
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
