//
// Created by Wiktor on 18.01.2017.
//

#include <algorithm>
#include <chrono>
#include "FixedAlgorithm.h"

FixedAlgorithm::FixedAlgorithm(std::shared_ptr<Problem> problem, size_t duration, unsigned numberOfPopulation)
        : IEvolutionaryAlgorithm(problem), duration(duration), numberOfPopulation(numberOfPopulation), currentPopulation(0),
            currentIteration(0){
    population = problem->generate();

}

std::vector<std::shared_ptr<IElement>> FixedAlgorithm::reproduce() {
    std::vector<std::shared_ptr<IElement>> population = std::move(getPopulation());
    std::vector<std::shared_ptr<IElement>> newPopulation;
    for (std::shared_ptr<IElement> &element: population) {
        std::vector<std::shared_ptr<IElement>> neighbours = problem->select(element);
        newPopulation.insert(newPopulation.end(), neighbours.begin(), neighbours.end());
    }
    connectIntoPairs(newPopulation, population.size());
    population.insert(newPopulation.end(), newPopulation.begin(), newPopulation.end());
    return population;
}

void FixedAlgorithm::success(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    currentPopulation += 1;
    if(currentIteration < duration){
        population = tempPopulation;
        return;
    }
    std::sort(connectedPairs.begin(), connectedPairs.end(),
              [&](std::pair<int, int> &a,std::pair<int, int> &b) -> bool {
                  return problem->rate(tempPopulation[a.first]) +  problem->rate(tempPopulation[a.second]) <
                          problem->rate(tempPopulation[b.first]) +  problem->rate(tempPopulation[b.second]);
              });
    population = std::vector<std::shared_ptr<IElement>>(tempPopulation.begin(),
                                                        tempPopulation.begin() +
                                                        std::min(tempPopulation.size(), problem->getPopulationSize()));
    currentIteration = 0;
    connectedPairs.clear();
}

std::vector<std::shared_ptr<IElement>> FixedAlgorithm::mutate(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    return std::vector<std::shared_ptr<IElement>>(tempPopulation);
}

std::vector<std::shared_ptr<IElement>>
FixedAlgorithm::crossover(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    return std::vector<std::shared_ptr<IElement>>(tempPopulation);
}

void FixedAlgorithm::connectIntoPairs(std::vector<std::shared_ptr<IElement>> &tempPopulation, size_t populationSize) {
    std::vector<int> myVec;
    for(int i = populationSize; i < populationSize + tempPopulation.size(); i++ )
        myVec.push_back( i );
    unsigned seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(myVec.begin(), myVec.end(), std::default_random_engine(seed));
    for(int i = 0; i< myVec.size()-1; i = i + 2) {
        std::pair<int, int> pair(myVec[i], myVec[i+1]);
        connectedPairs.push_back(pair);
    }
}

bool FixedAlgorithm::finish() {
    return currentPopulation > numberOfPopulation;
}



