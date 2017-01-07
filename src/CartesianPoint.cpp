#include <random>
#include <chrono>
#include "CartesianPoint.h"


std::shared_ptr<IElement> CartesianPoint::mutate() {
    unsigned seed = (unsigned int) std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_real_distribution<double> distribution(-0.3, 0.3);
    std::default_random_engine generator(seed);
    double newX = x + distribution(generator);
    double newY = y + distribution(generator);
    return std::make_shared<CartesianPoint>(newX, newY);
}

std::shared_ptr<IElement> CartesianPoint::crossover(std::vector<std::shared_ptr<IElement>> &vector) {
    double accX = 0.0;
    double accY = 0.0;

    for (std::shared_ptr<IElement> element: vector) {
        auto cartesianPoint = std::static_pointer_cast<CartesianPoint>(element);
        accX += cartesianPoint->x;
        accY += cartesianPoint->y;
    }

    accX /= vector.size();
    accY /= vector.size();

    return std::make_shared<CartesianPoint>((x + accX) / 2, (y + accY) / 2);

}

CartesianPoint::CartesianPoint(double x, double y) : x(x), y(y) {}

double CartesianPoint::getX() const {
    return x;
}

double CartesianPoint::getY() const {
    return y;
}
