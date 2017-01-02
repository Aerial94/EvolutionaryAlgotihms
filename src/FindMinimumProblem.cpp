#include <random>
#include <chrono>
#include "FindMinimumProblem.h"
#include "CartesianPoint.h"

const double FindMinimumProblem::DIFFRENCE = 0.005;
const size_t FindMinimumProblem::POPULATION_SIZE = 20;


std::vector<std::shared_ptr<IElement>> FindMinimumProblem::select(std::shared_ptr<IElement> &point) {
    std::vector<std::shared_ptr<IElement>> newPoints;
    auto cartesianPoint = std::static_pointer_cast<CartesianPoint>(point);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;
            newPoints.push_back(std::make_shared<CartesianPoint>(cartesianPoint->getX() + DIFFRENCE * i,
                                                                 cartesianPoint->getY() + DIFFRENCE * i));
        }
    }
    return newPoints;
}

long FindMinimumProblem::rate(std::shared_ptr<IElement> &point) {
    return 0;
}

std::vector<std::shared_ptr<IElement>> FindMinimumProblem::generate() {
    unsigned seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_real_distribution<double> distribution(-100.0, 100.0);
    std::default_random_engine generator(seed);
    std::vector<std::shared_ptr<IElement>> newPoints;

    for (int i = 0; i < POPULATION_SIZE; ++i) {
        newPoints.push_back(std::make_shared<CartesianPoint>(distribution(generator), distribution(generator)));
    }
    return newPoints;
}
