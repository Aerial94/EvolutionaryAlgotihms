#ifndef EVOLUTIONARYALGOTIHMS_RUNNER_H
#define EVOLUTIONARYALGOTIHMS_RUNNER_H


#include <memory>
#include "IEvolutionaryAlgorithm.h"


class Runner {
public:
    Runner(std::shared_ptr<IEvolutionaryAlgorithm> algorithm) : algorithm(algorithm) {}
    virtual ~Runner();
    std::vector<std::shared_ptr<IElement>> run();
protected:
    std::shared_ptr<IEvolutionaryAlgorithm> algorithm;

};


#endif //EVOLUTIONARYALGOTIHMS_RUNNER_H
