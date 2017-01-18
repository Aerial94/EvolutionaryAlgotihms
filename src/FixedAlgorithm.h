//
// Created by Wiktor on 18.01.2017.
//

#ifndef EVOLUTIONARYALGOTIHMS_FIXEDALGORITHM_H
#define EVOLUTIONARYALGOTIHMS_FIXEDALGORITHM_H


#include "IEvolutionaryAlgorithm.h"

class FixedAlgorithm : public IEvolutionaryAlgorithm{

public:

    FixedAlgorithm(std::shared_ptr<Problem> problem, size_t duration, unsigned numberOfPopulation);

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
    void connectIntoPairs(std::vector<std::shared_ptr<IElement>> &tempPopulation, size_t populationSize);
    std::vector<std::pair<int, int>> connectedPairs;
    unsigned currentIteration;
    unsigned currentPopulation;
    unsigned duration;
    unsigned numberOfPopulation;
};


#endif //EVOLUTIONARYALGOTIHMS_FIXEDALGORITHM_H
