#include "StandardEvolutionaryAlgorithm.h"
#include <random>
#include <chrono>
#include <algorithm>

StandardEvolutionaryAlgorithm::StandardEvolutionaryAlgorithm(const std::shared_ptr<Problem> problem)
        : currentPopulation(0), problem(problem) {
    population = problem.generate();
    theWorstElements = std::vector<IElement>(population.end() - std::min(population.size(), CROSSOVER_POINTS), population.end());
    maxElement = tempPopulation[0];
}

std::vector <IElement> StandardEvolutionaryAlgorithm::crossover(const std::vector <IElement> &tempPopulation) {
    std::vector <IElement> newPopulation(tempPopulation.begin(), tempPopulation.end());
    std::for_each(theWorstElements.begin(), theWorstElements.end(), [](IElement &element) -> IElement {
        newPopulation.push_back(element.crossover(maxElement));
    });
    return newPopulation;
}

std::vector <IElement> StandardEvolutionaryAlgorithm::mutate(std::vector <IElement> &tempPopulation) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(tempPopulation.begin(), tempPopulation.end(), std::default_random_engine(seed));
    std::vector <IElement> mutatedPopulation;
    int i = 0;

    for (IElement element: tempPopulation) {
        if (++i > MUTATION_SIZE) {
            mutatedPopulation.push_back(element);
        } else {
            mutatedPopulation.push_back(element.crossover());
        }
    }
    return mutatedPopulation;
}

std::vector <IElement> StandardEvolutionaryAlgorithm::reproduce() {
    std::vector <IElement> population = getPopulation();
    std::vector <IElement> newPopulation;
    for (IElement element: population) {
        std::vector <IElement> neighbours = problem->select(element);
        newPopulation.splice(newPopulation.end(), neighbours);
        newPopulation.push_back(element);
    }
    return newPopulation;
}

void StandardEvolutionaryAlgorithm::success(std::vector <IElement> &tempPopulation) {
    std::sort(tempPopulation.begin(), tempPopulation.end(), [](const IElement &a, const IElement &b) -> bool {
        return problem->rate(a) > problem->rate(b);
    });
    population = std::vector<IElement>(tempPopulation.begin(),
                                       tempPopulation.begin() + std::min(tempPopulation.size(), POPULATION_SIZE));
    theWorstElements = std::vector<IElement>(tempPopulation.end() - std::min(newPopulation.size(), CROSSOVER_POINTS),
                                             newPopulation.end());
    maxElement = tempPopulation[0];
    currentPopulation += 1;
}

bool StandardEvolutionaryAlgorithm::finish() {
    return currentPopulation > POPULATION_SIZE;
}