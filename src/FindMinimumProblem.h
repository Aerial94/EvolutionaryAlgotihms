#ifndef EVOLUTIONARYALGOTIHMS_FINDMINIMUMPROBLEM_H
#define EVOLUTIONARYALGOTIHMS_FINDMINIMUMPROBLEM_H


#include "Problem.h"

class FindMinimumProblem : public Problem {
public:
    size_t populationSize;

    FindMinimumProblem(size_t populationSize, double difference)
            : populationSize(populationSize), difference(difference) {};

    std::vector<std::shared_ptr<IElement>> select(std::shared_ptr<IElement> &point) override;

    double rate(std::shared_ptr<IElement> &point) override;

    std::vector<std::shared_ptr<IElement>> generate() override;

    size_t getPopulationSize() override;

private:
    double difference;
};


#endif //EVOLUTIONARYALGOTIHMS_FINDMINIMUMPROBLEM_H
