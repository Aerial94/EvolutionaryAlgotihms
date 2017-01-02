
#ifndef EVOLUTIONARYALGOTIHMS_CARTESIANPOINT_H
#define EVOLUTIONARYALGOTIHMS_CARTESIANPOINT_H


#include "IElement.h"

class CartesianPoint : public IElement{

public:
    CartesianPoint(double x, double y);

    std::shared_ptr<IElement> mutate() override;

    std::shared_ptr<IElement> crossover(std::vector<std::shared_ptr<IElement>>& vector) override;

    double getX() const;

    double getY() const;

private:
    double x;
    double y;
};


#endif //EVOLUTIONARYALGOTIHMS_CARTESIANPOINT_H
