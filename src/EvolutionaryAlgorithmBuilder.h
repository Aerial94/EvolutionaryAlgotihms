#ifndef EVOLUTIONARYALGOTIHMS_EVOLUTIONARYALGORITHMBUILDER_H
#define EVOLUTIONARYALGOTIHMS_EVOLUTIONARYALGORITHMBUILDER_H

#include "IEvolutionaryAlgorithm.h"
#include "SimpleEvolutionaryAlgorithm.h"
#include "StandardEvolutionaryAlgorithm.h"
#include "FixedAlgorithm.h"


class EvolutionaryAlgorithmBuilder {
public:
    static const int SIMPLE_ALGORITHM = 0;
    static const int STANDARD_ALGORITHM = 1;
    static const int FIXED_ALGORITHM = 2;

    EvolutionaryAlgorithmBuilder(int algorithmType, std::shared_ptr<Problem> &problem) {
        this->algorithmType = algorithmType;
        this->problem = problem;
    }

    EvolutionaryAlgorithmBuilder* withMaxTime(unsigned maxTime) {
        this->maxTime = maxTime;
        return this;
    }

    EvolutionaryAlgorithmBuilder* withTournamentSize(unsigned tournamentSize) {
        this->tournamentSize = tournamentSize;
        return this;
    }

    EvolutionaryAlgorithmBuilder* withCrossoverChance(double crossoverChance) {
        this->crossoverChance = crossoverChance;
        return this;
    }

    EvolutionaryAlgorithmBuilder* withCrossoverPoints(unsigned crossoverPoints) {
        this->crossoverPoints = crossoverPoints;
        return this;
    }

    EvolutionaryAlgorithmBuilder* withMutationSize(size_t mutationSize) {
        this->mutationSize = maxTime;
        return this;
    }

    EvolutionaryAlgorithmBuilder* withNumberOfPopulation(unsigned numberOfPopulation) {
        this->numberOfPopulation = numberOfPopulation;
        return this;
    }

    EvolutionaryAlgorithmBuilder* withDuration(size_t duration) {
        this->duration = duration;
        return this;
    }

    IEvolutionaryAlgorithm* build() {
        switch (algorithmType) {
            case SIMPLE_ALGORITHM:
                return new SimpleEvolutionaryAlgorithm(problem, maxTime, tournamentSize, crossoverChance);
            case STANDARD_ALGORITHM:
                return new StandardEvolutionaryAlgorithm(problem, crossoverPoints, mutationSize, numberOfPopulation);
            case FIXED_ALGORITHM:
                return new FixedAlgorithm(problem, duration, numberOfPopulation);
            default:
                return nullptr;
        }
    }

private:
    std::shared_ptr<Problem> problem;
    int algorithmType;
    unsigned maxTime = 5;
    unsigned tournamentSize = 5;
    double crossoverChance = 0.15;
    size_t crossoverPoints = 5;
    size_t mutationSize = 4;
    size_t duration = 5;
    unsigned numberOfPopulation = 1000;
};


#endif //EVOLUTIONARYALGOTIHMS_EVOLUTIONARYALGORITHMBUILDER_H
