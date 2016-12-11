#ifndef EVOLUTIONARYALGOTIHMS_IEVOLUTIONARYALGORITHM_H
#define EVOLUTIONARYALGOTIHMS_IEVOLUTIONARYALGORITHM_H


#include <list>
#include "IElement.h"


class IEvolutionaryAlgorithm {
public:
    virtual ~IEvolutionaryAlgorithm() {}
    virtual IEvolutionaryAlgorithm(const Problem& problem);
    virtual std::vector<IElement> crossover(std::vector<IElement>& tempPopulation) = 0;
    virtual std::vector<IElement> mutate(std::vector<IElement>& tempPopulation) = 0;
    virtual std::vector<IElement> reproduce() = 0;
    virtual void success(std::list<IElement>& tempPopulation) = 0;
    virtual bool finish() = 0;

    const std::vector<IElement> getPopulation() const {
        return population;
    }

protected:
    std::shared_ptr<Problem> problem;
    std::vector<IElement> population;
};


#endif //EVOLUTIONARYALGOTIHMS_IEVOLUTIONARYALGORITHM_H
