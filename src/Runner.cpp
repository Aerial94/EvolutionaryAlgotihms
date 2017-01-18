#include <vector>
#include <algorithm>
#include "iostream"
#include "Runner.h"
#include "CartesianPoint.h"

Runner::~Runner() {

}

std::vector<std::shared_ptr<IElement>> Runner::run() {
    algorithm->init();
    while (!algorithm->finish()) {
        std::vector<std::shared_ptr<IElement>> p1 = algorithm->reproduce();
        std::vector<std::shared_ptr<IElement>> p2 = algorithm->mutate(p1);
        std::vector<std::shared_ptr<IElement>> p3 = algorithm->crossover(p2);
        algorithm->success(p3);
    }
    return algorithm->getPopulation();
}


