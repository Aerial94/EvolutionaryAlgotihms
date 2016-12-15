#ifndef EVOLUTIONARYALGOTIHMS_PROBLEM_H
#define EVOLUTIONARYALGOTIHMS_PROBLEM_H

#include <list>
#include <vector>
#include "IElement.h"

class Problem {
public:
    virtual std::vector<std::shared_ptr<IElement>> select(IElement& point) = 0;
    virtual long rate(std::shared_ptr<IElement>& point) = 0;
    virtual std::vector<std::shared_ptr<IElement>> generate() = 0;
protected:
};


#endif //EVOLUTIONARYALGOTIHMS_PROBLEM_H
