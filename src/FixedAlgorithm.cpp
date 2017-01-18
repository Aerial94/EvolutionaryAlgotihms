//
// Created by Wiktor on 18.01.2017.
//

#include <algorithm>
#include <chrono>
#include "FixedAlgorithm.h"
#include <iostream>

FixedAlgorithm::FixedAlgorithm(std::shared_ptr<Problem> problem, size_t duration, unsigned numberOfPopulation)
        : IEvolutionaryAlgorithm(problem), duration(duration), numberOfPopulation(numberOfPopulation), currentPopulation(0),
            currentIteration(0){
    population = problem->generate();
    connectIntoPairs(population, 0);

}

std::vector<std::shared_ptr<IElement>> FixedAlgorithm::reproduce() {
    std::vector<std::shared_ptr<IElement>> population = std::move(getPopulation());
    std::vector<std::shared_ptr<IElement>> newPopulation;
    unsigned seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, population.size() - 1);
    for (int i = 0 ; i < 2; ++i) {
        std::shared_ptr<IElement> element = population[distribution(generator)];
        std::vector<std::shared_ptr<IElement>> neighbours = problem->select(element);
        newPopulation.insert(newPopulation.end(), neighbours.begin(), neighbours.end());
    }
    connectIntoPairs(newPopulation, population.size());
    population.insert(population.end(), newPopulation.begin(), newPopulation.end());
    return population;
}

void FixedAlgorithm::success(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    currentPopulation += 1;
    if(currentIteration < duration){
        ++currentIteration;
        population = tempPopulation;
        return;
    }
    std::vector<std::pair<int, int>> temp(connectedPairs);
    std::sort(temp.begin(), temp.end(),
              [&](const std::pair<int, int>& a, const std::pair<int, int>& b) -> bool {
                  double first = problem->rate(tempPopulation[a.first]) +  problem->rate(tempPopulation[a.second]);
                  double second = problem->rate(tempPopulation[b.first]) +  problem->rate(tempPopulation[b.second]);
                  return first > second;
              });
    std::vector<std::shared_ptr<IElement>> newPopulation;

    for(std::pair<int,int> pair: temp) {
        if(newPopulation.size() < problem->getPopulationSize()) {
            newPopulation.push_back(tempPopulation[pair.first]);
            newPopulation.push_back(tempPopulation[pair.second]);
        } else {
            break;
        }
    }
    population = std::vector<std::shared_ptr<IElement>>(newPopulation);
    currentIteration = 0;
    connectedPairs = std::vector<std::pair<int, int>>();
}

std::vector<std::shared_ptr<IElement>> FixedAlgorithm::mutate(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    std::vector<std::shared_ptr<IElement>> newPopulation;
    for(std::shared_ptr<IElement> element: tempPopulation) {
        newPopulation.push_back(element->mutate());
    }
    return std::vector<std::shared_ptr<IElement>>(tempPopulation);
}

std::vector<std::shared_ptr<IElement>>
FixedAlgorithm::crossover(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    return std::vector<std::shared_ptr<IElement>>(tempPopulation);
}

void FixedAlgorithm::connectIntoPairs(std::vector<std::shared_ptr<IElement>> &tempPopulation, size_t populationSize) {
    std::vector<int> myVec;
    for(int i = populationSize; i < populationSize + tempPopulation.size(); i++ )
        myVec.push_back(i);
    unsigned seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();
    std::cout<<myVec.size()<<std::endl;

    std::shuffle(myVec.begin(), myVec.end(), std::default_random_engine(seed));
    for(int i = 0; i < myVec.size()-1; i = i + 2) {
        std::pair<int, int> pair(myVec[i], myVec[i+1]);
        connectedPairs.push_back(pair);
    }
}

bool FixedAlgorithm::finish() {

    return currentPopulation > numberOfPopulation;
}



