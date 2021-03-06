#ifndef EVOLUTIONARYALGOTIHMS_SIMPLEEVOLUTIONARYALGORITHM_H
#define EVOLUTIONARYALGOTIHMS_SIMPLEEVOLUTIONARYALGORITHM_H

#include <vector>
#include <cstdio>
#include <memory>
#include <chrono>
#include "IEvolutionaryAlgorithm.h"
#include "Problem.h"

class SimpleEvolutionaryAlgorithm : public IEvolutionaryAlgorithm {
public:

    SimpleEvolutionaryAlgorithm(std::shared_ptr<Problem> problem, unsigned maxTime, unsigned tournamentSize, double crossoverChance);

    virtual std::vector<std::shared_ptr<IElement>>
    crossover(std::vector<std::shared_ptr<IElement>> &tempPopulation) override;

    virtual std::vector<std::shared_ptr<IElement>>
    mutate(std::vector<std::shared_ptr<IElement>> &tempPopulation) override;

    virtual std::vector<std::shared_ptr<IElement>> reproduce() override;

    virtual void success(std::vector<std::shared_ptr<IElement>> &tempPopulation) override;

    virtual bool finish() override;

    virtual void init() override;

    unsigned getCurrentPopulation() { return currentPopulation; }

private:
    std::chrono::system_clock::time_point startTime;
    unsigned currentPopulation;
    unsigned maxTime ;
    unsigned tournamentSize;
    double crossoverChance ;

};


#endif //EVOLUTIONARYALGOTIHMS_SIMPLEEVOLUTIONARYALGORITHM_H
