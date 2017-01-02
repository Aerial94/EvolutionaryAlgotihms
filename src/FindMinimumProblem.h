#ifndef EVOLUTIONARYALGOTIHMS_FINDMINIMUMPROBLEM_H
#define EVOLUTIONARYALGOTIHMS_FINDMINIMUMPROBLEM_H


#include "Problem.h"

class FindMinimumProblem : public Problem{
public:
    static const size_t POPULATION_SIZE;

    std::vector<std::shared_ptr<IElement>> select(std::shared_ptr<IElement> &point) override;

    long rate(std::shared_ptr<IElement> &point) override;

    std::vector<std::shared_ptr<IElement>> generate() override;

private:
    double static const DIFFRENCE;
};


#endif //EVOLUTIONARYALGOTIHMS_FINDMINIMUMPROBLEM_H
