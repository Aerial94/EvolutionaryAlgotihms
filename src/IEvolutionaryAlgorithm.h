#ifndef EVOLUTIONARYALGOTIHMS_IEVOLUTIONARYALGORITHM_H
#define EVOLUTIONARYALGOTIHMS_IEVOLUTIONARYALGORITHM_H

#include "IElement.h"
#include "Problem.h"

class IEvolutionaryAlgorithm {
public:
    virtual ~IEvolutionaryAlgorithm() {}
    IEvolutionaryAlgorithm(std::shared_ptr<Problem> problem) : problem(problem){};
    virtual std::vector<std::shared_ptr<IElement>> crossover(std::vector<std::shared_ptr<IElement>>& tempPopulation) = 0;
    virtual std::vector<std::shared_ptr<IElement>> mutate(std::vector<std::shared_ptr<IElement>>& tempPopulation) = 0;
    virtual std::vector<std::shared_ptr<IElement>> reproduce() = 0;
    virtual void success(std::vector<std::shared_ptr<IElement>>& tempPopulation) = 0;
    virtual bool finish() = 0;
    virtual void init() = 0;

    std::vector<std::shared_ptr<IElement>> const& getPopulation() const {
        return population;
    }

protected:
    std::shared_ptr<Problem> problem;
    std::vector<std::shared_ptr<IElement>> population;
};


#endif //EVOLUTIONARYALGOTIHMS_IEVOLUTIONARYALGORITHM_H
