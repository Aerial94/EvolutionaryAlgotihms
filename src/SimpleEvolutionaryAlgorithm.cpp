#include "SimpleEvolutionaryAlgorithm.h"

#include "FindMinimumProblem.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>

SimpleEvolutionaryAlgorithm::SimpleEvolutionaryAlgorithm(
        std::shared_ptr<Problem> problem, unsigned maxTime, unsigned tournamentSize, double crossoverChance)
        : IEvolutionaryAlgorithm(problem), maxTime(maxTime), tournamentSize(tournamentSize), crossoverChance(crossoverChance) {
    currentPopulation = 0;
    population = problem->generate();
}

std::vector<std::shared_ptr<IElement>>
SimpleEvolutionaryAlgorithm::mutate(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    std::vector<std::shared_ptr<IElement>> mutatedPopulation;
    for (std::shared_ptr<IElement> &element: tempPopulation) {
        mutatedPopulation.push_back(element->mutate());
    }
    return mutatedPopulation;
}

std::vector<std::shared_ptr<IElement>> SimpleEvolutionaryAlgorithm::reproduce() {
    std::vector<std::shared_ptr<IElement>> population = std::move(getPopulation());
    return population;
}

void SimpleEvolutionaryAlgorithm::success(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    population = std::vector<std::shared_ptr<IElement>>();
    unsigned seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<std::shared_ptr<IElement>> tournamentElements = std::vector<std::shared_ptr<IElement>>();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, tempPopulation.size() - 1);
    for (int i = 0; i < tempPopulation.size(); i++) {
        for (int j = 0; j < tournamentSize; j++) {
            tournamentElements.push_back(std::move(tempPopulation[distribution(generator)]));
        }
        auto tournamentWinner = std::max_element(tournamentElements.begin(), tournamentElements.end(),
        [&](std::shared_ptr<IElement> &a, std::shared_ptr<IElement> &b){
            return problem->rate(a) < problem->rate(b);
        });
        population.push_back(*tournamentWinner);
        tournamentElements.clear();
    }
    currentPopulation += 1;
}

bool SimpleEvolutionaryAlgorithm::finish() {
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - startTime);
    return duration.count() > maxTime;
}

void SimpleEvolutionaryAlgorithm::init() {
    startTime = std::chrono::system_clock::now();
}

std::vector<std::shared_ptr<IElement>>
SimpleEvolutionaryAlgorithm::crossover(std::vector<std::shared_ptr<IElement>> &tempPopulation) {
    std::vector<std::shared_ptr<IElement>> newPopulation;
    unsigned seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> doubleDistribution(0.0,1.0);
    std::uniform_int_distribution<int> intDistribution(0 , tempPopulation.size() - 1);
    for (std::shared_ptr<IElement> &element: tempPopulation) {
        if (doubleDistribution(generator) < crossoverChance) {
            std::vector<std::shared_ptr<IElement>> randomElement { tempPopulation[intDistribution(generator)]};
            newPopulation.push_back(element->crossover(randomElement));
        } else {
            newPopulation.push_back(element);
        }
    }
    return newPopulation;
}