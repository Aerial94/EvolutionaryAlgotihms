#include <random>
#include <chrono>
#include "FindMinimumProblem.h"
#include "CartesianPoint.h"

std::vector<std::shared_ptr<IElement>> FindMinimumProblem::select(std::shared_ptr<IElement> &point) {
    std::vector<std::shared_ptr<IElement>> newPoints;
    auto cartesianPoint = std::static_pointer_cast<CartesianPoint>(point);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;
            newPoints.push_back(std::make_shared<CartesianPoint>(cartesianPoint->getX() + difference * i,
                                                                 cartesianPoint->getY() + difference * i));
        }
    }
    return newPoints;
}

double FindMinimumProblem::rate(std::shared_ptr<IElement> &point) {
    auto cartesianPoint = std::static_pointer_cast<CartesianPoint>(point);
    return - cartesianPoint->getX() * cartesianPoint->getX() - cartesianPoint->getY() * cartesianPoint->getY();
}

std::vector<std::shared_ptr<IElement>> FindMinimumProblem::generate() {
    unsigned seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_real_distribution<double> distribution(-100.0, 100.0);
    std::default_random_engine generator(seed);
    std::vector<std::shared_ptr<IElement>> newPoints;

    for (int i = 0; i < populationSize; ++i) {
        newPoints.push_back(std::make_shared<CartesianPoint>(distribution(generator), distribution(generator)));
    }
    return newPoints;
}

size_t FindMinimumProblem::getPopulationSize() {
    return populationSize;
}
