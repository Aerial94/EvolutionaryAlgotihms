#ifndef EVOLUTIONARYALGOTIHMS_IEVOLUTIONARYALGORITHM_H
#define EVOLUTIONARYALGOTIHMS_IEVOLUTIONARYALGORITHM_H


#include <list>
#include "IElement.h"


class IEvolutionaryAlgorithm {
public:
    virtual ~IEvolutionaryAlgorithm() {}

    virtual std::list<IElement> crossover() = 0;
    virtual std::list<IElement> mutate() = 0;
    virtual std::list<IElement> reproduce() = 0;
    virtual std::list<IElement> success() = 0;
    virtual bool finish() = 0;

    const std::list<IElement> getPopulation() const {
        return population;
    }

protected:
    std::list<IElement> population;

};


#endif //EVOLUTIONARYALGOTIHMS_IEVOLUTIONARYALGORITHM_H
