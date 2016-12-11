#include "Runner.h"

Runner::~Runner() {

}

std::vector<IElement> Runner::run() {
    while (not algorithm->finish()) {
        algorithm->reproduce();
        algorithm->crossover();
        algorithm->mutate();
        algorithm->success();
    }
    return algorithm->getPopulation();
}


