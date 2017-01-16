#ifndef EVOLUTIONARYALGOTIHMS_STANDARDEVOLUTIONARYALGORITHM_H
#define EVOLUTIONARYALGOTIHMS_STANDARDEVOLUTIONARYALGORITHM_H

#include <vector>
#include <cstdio>
#include <memory>
#include "IEvolutionaryAlgorithm.h"
#include "Problem.h"

class StandardEvolutionaryAlgorithm : public IEvolutionaryAlgorithm {
public:

    StandardEvolutionaryAlgorithm(std::shared_ptr<Problem> problem, size_t crossoverPoints, size_t mutationSize, unsigned numberOfPopulation);

    virtual std::vector<std::shared_ptr<IElement>>
    crossover(std::vector<std::shared_ptr<IElement>> &tempPopulation) override;

    virtual std::vector<std::shared_ptr<IElement>>
    mutate(std::vector<std::shared_ptr<IElement>> &tempPopulation) override;

    virtual std::vector<std::shared_ptr<IElement>> reproduce() override;

    virtual void success(std::vector<std::shared_ptr<IElement>> &tempPopulation) override;

    virtual bool finish() override;

    virtual void init() {};

    unsigned getCurrentPopulation() { return currentPopulation; }

private:
    std::shared_ptr<IElement> maxElement;
    std::vector<std::shared_ptr<IElement>> theWorstElements;
    unsigned currentPopulation;
    size_t crossoverPoints;
    size_t mutationSize;
    unsigned numberOfPopulation;

};


#endif //EVOLUTIONARYALGOTIHMS_STANDARDEVOLUTIONARYALGORITHM_H
