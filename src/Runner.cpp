#include <vector>
#include <algorithm>
#include "iostream"
#include "Runner.h"
#include "CartesianPoint.h"

Runner::~Runner() {

}

std::vector<std::shared_ptr<IElement>> Runner::run() {
    std::vector<std::shared_ptr<IElement>> pop = algorithm->getPopulation();
    std::for_each(pop.begin(), pop.end(), [](std::shared_ptr<IElement> &a) {
        auto cartesianPoint = std::static_pointer_cast<CartesianPoint>(a);
        std::cout << cartesianPoint->getX() << " " << cartesianPoint->getY() << std::endl;
    });
    return algorithm->getPopulation();
}


