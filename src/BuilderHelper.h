#ifndef EVOLUTIONARYALGOTIHMS_BUILDERHELPER_H
#define EVOLUTIONARYALGOTIHMS_BUILDERHELPER_H


#include "IEvolutionaryAlgorithm.h"

class BuilderHelper {
public:
    std::shared_ptr<IEvolutionaryAlgorithm> createAlgorithm();


};


#endif //EVOLUTIONARYALGOTIHMS_BUILDERHELPER_H
