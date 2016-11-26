#include "Runner.h"

Runner::~Runner() {

}

std::list<IElement> Runner::run() {
    while (not algorithm->finish()) {
        algorithm->reproduce();
        algorithm->crossover();
        algorithm->mutate();
        algorithm->success();
    }
    return algorithm->getPopulation();
}


