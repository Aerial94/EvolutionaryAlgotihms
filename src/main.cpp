#include <memory>
#include "Problem.h"
#include "IEvolutionaryAlgorithm.h"
#include "StandardEvolutionaryAlgorithm.h"
#include "Runner.h"
#include "FindMinimumProblem.h"

#define CATCH_CONFIG_MAIN

int main(int argc, char* argv[])  {
    std::unique_ptr<Problem> problem(new FindMinimumProblem());
    std::unique_ptr<IEvolutionaryAlgorithm> algorithm(new StandardEvolutionaryAlgorithm(std::move(problem)));
    Runner runner(std::move(algorithm));
    runner.run();
    return 0;
}