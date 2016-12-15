#ifndef EVOLUTIONARYALGOTIHMS_POINT_H
#define EVOLUTIONARYALGOTIHMS_POINT_H

#include<list>
#include <vector>
#include <memory>

class IElement {
public:
    virtual std::shared_ptr<IElement>& mutate() = 0;
    virtual std::shared_ptr<IElement>& crossover(std::vector<std::shared_ptr<IElement>>) = 0;
};


#endif //EVOLUTIONARYALGOTIHMS_POINT_H
