#ifndef EVOLUTIONARYALGOTIHMS_STANDARDEVOLUTIONARYALGORITHM_H
#define EVOLUTIONARYALGOTIHMS_STANDARDEVOLUTIONARYALGORITHM_H

#include "IEvolutionaryAlgorithm.h"

class StandardEvolutionaryAlgorithm : public IEvolutionaryAlgorithm {
public:
    std::list<IElement> crossover() override;

    std::list<IElement> mutate() override;

    std::list<IElement> reproduce() override;

    std::list<IElement> success() override;
};


#endif //EVOLUTIONARYALGOTIHMS_STANDARDEVOLUTIONARYALGORITHM_H
