#ifndef EVOLUTIONARYALGOTIHMS_PROBLEM_H
#define EVOLUTIONARYALGOTIHMS_PROBLEM_H

#include <list>
#include "IElement.h"

class Problem {
public:
    virtual std::vector<IElement> select(IElement& point) = 0;
    virtual long rate(IElement& point) = 0;
    virtual long generate() = 0;
protected:
};


#endif //EVOLUTIONARYALGOTIHMS_PROBLEM_H
