#ifndef EVOLUTIONARYALGOTIHMS_FINDMINIMUMPROBLEMBUILDER_H
#define EVOLUTIONARYALGOTIHMS_FINDMINIMUMPROBLEMBUILDER_H

#include "Problem.h"
#include "FindMinimumProblem.h"

class FindMinimumProblemBuilder {
public:
    FindMinimumProblemBuilder() {}

    FindMinimumProblemBuilder* withDifference(double difference) {
        this->difference = difference;
        return this;
    }

    FindMinimumProblemBuilder* withPopulationSize(unsigned populationSize) {
        this->populationSize = populationSize;
        return this;
    }

    FindMinimumProblem* build() {
        return new FindMinimumProblem(populationSize, difference);
    }

private:
    double difference = 0.05;
    unsigned populationSize = 20;
};


#endif //EVOLUTIONARYALGOTIHMS_FINDMINIMUMPROBLEMBUILDER_H
