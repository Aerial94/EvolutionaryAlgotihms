#ifndef EVOLUTIONARYALGOTIHMS_POINT_H
#define EVOLUTIONARYALGOTIHMS_POINT_H

#include<list>

class IElement {
public:
    virtual ~IElement() {};
    virtual IElement mutate() = 0;
    virtual IElement crossover(std::list<IElement>) = 0;
};


#endif //EVOLUTIONARYALGOTIHMS_POINT_H
