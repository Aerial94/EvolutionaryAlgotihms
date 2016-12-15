#ifndef EVOLUTIONARYALGOTIHMS_STANDARDEVOLUTIONARYALGORITHM_H
#define EVOLUTIONARYALGOTIHMS_STANDARDEVOLUTIONARYALGORITHM_H

#include <vector>
#include <cstdio>
#include <memory>
#include "IEvolutionaryAlgorithm.h"
#include "Problem.h"

class StandardEvolutionaryAlgorithm : public IEvolutionaryAlgorithm {
public:

    StandardEvolutionaryAlgorithm(std::unique_ptr<Problem> &problem);

    virtual std::vector<std::shared_ptr<IElement>> crossover(std::vector<std::shared_ptr<IElement>>& tempPopulation) override;

    virtual  std::vector<std::shared_ptr<IElement>> mutate(std::vector<std::shared_ptr<IElement>>& tempPopulation) override;

    virtual std::vector<std::shared_ptr<IElement>> reproduce() override;

    virtual void success(std::vector<std::shared_ptr<IElement>>& tempPopulation) override;

    virtual bool finish() override;

private:
    std::unique_ptr<Problem> problem;
    std::shared_ptr<IElement> maxElement;
    std::vector<std::shared_ptr<IElement>> theWorstElements;
    unsigned currentPopulation;
    const size_t POPULATION_SIZE = 20;
    const size_t CROSSOVER_POINTS = 5;
    const size_t MUTATION_SIZE = 4;
    const unsigned NUMBER_OF_POPULATION = 1000;
};


#endif //EVOLUTIONARYALGOTIHMS_STANDARDEVOLUTIONARYALGORITHM_H
