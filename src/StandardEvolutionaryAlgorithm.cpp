#include "StandardEvolutionaryAlgorithm.h"
#include <random>
#include <chrono>
#include <algorithm>

std::vector<IElement> StandardEvolutionaryAlgorithm::crossover(std::vector<IElement>& tempPopulation) {

}

std::vector<IElement> StandardEvolutionaryAlgorithm::mutate(std::vector<IElement>& tempPopulation) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle (tempPopulation.begin(), tempPopulation.end(), std::default_random_engine(seed));
    std::vector<IElement> mutatedPopulation;
    int i = 0;

    for(IElement element: tempPopulation) {
        if(++i > MUTATION_SIZE) {
            mutatedPopulation.push_back(element);
        } else {
            mutatedPopulation.push_back(element.crossover());
        }
    }
    return mutatedPopulation;
}

std::vector<IElement> StandardEvolutionaryAlgorithm::reproduce() {
    std::vector<IElement> population = getPopulation();
    std::vector<IElement> newPopulation;
    for(IElement element: population) {
        std::vector<IElement> neighbours = element.getNeighbour();
        newPopulation.splice(newPopulation.end(), neighbours);
        newPopulation.push_back(element);
    }
    return newPopulation;
}

void StandardEvolutionaryAlgorithm::success(std::vector<IElement>& tempPopulation) {
    std::sort(tempPopulation.begin(), tempPopulation.end(), [](const IElement& a, const IElement& b) -> bool {
        return a.fitness() > b.fitness();
    });

    std::vector<IElement> newPopulation(tempPopulation.begin(), tempPopulation.begin() + POPULATION_SIZE);
    population = newPopulation;
    maxElement = population[0];
    std::vector<IElement> worst(tempPopulation.end() -  std::min(tempPopulation.size(), CROSSOVER_POINTS), tempPopulation.end());
    theWorstElements = worst;

}

bool StandardEvolutionaryAlgorithm::finish() {

}