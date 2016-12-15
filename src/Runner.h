#ifndef EVOLUTIONARYALGOTIHMS_RUNNER_H
#define EVOLUTIONARYALGOTIHMS_RUNNER_H


#include <memory>
#include "IEvolutionaryAlgorithm.h"


class Runner {
public:
    Runner(std::unique_ptr<IEvolutionaryAlgorithm> algorithm) : algorithm(std::move(algorithm)) {}
    virtual ~Runner();
    std::vector<std::shared_ptr<IElement>> run();
protected:
    std::unique_ptr<IEvolutionaryAlgorithm> algorithm;

};


#endif //EVOLUTIONARYALGOTIHMS_RUNNER_H
