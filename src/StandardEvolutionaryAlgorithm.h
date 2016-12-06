#ifndef EVOLUTIONARYALGOTIHMS_STANDARDEVOLUTIONARYALGORITHM_H
#define EVOLUTIONARYALGOTIHMS_STANDARDEVOLUTIONARYALGORITHM_H

#include "IEvolutionaryAlgorithm.h"

class StandardEvolutionaryAlgorithm : public IEvolutionaryAlgorithm {
public:
    virtual std::vector<IElement> crossover(std::vector<IElement>& tempPopulation) override;

    virtual  std::vector<IElement> mutate(std::vector<IElement>& tempPopulation) override;

    virtual std::vector<IElement> reproduce() override;

    virtual std::vector<IElement> success(std::vector<IElement>& tempPopulation) override;

    virtual bool finish() override;

private:
    IElement maxElement;
    std::vector<IElement> theWorstElements;
    const size_t POPULATION_SIZE = 20;
    const size_t CROSSOVER_POINTS = 5;
    const size_t MUTATION_SIZE = 4;
};


#endif //EVOLUTIONARYALGOTIHMS_STANDARDEVOLUTIONARYALGORITHM_H
