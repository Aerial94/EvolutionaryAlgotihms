#include <memory>
#include <iostream>
#include "Problem.h"
#include "IEvolutionaryAlgorithm.h"
#include "StandardEvolutionaryAlgorithm.h"
#include "Runner.h"
#include "SimpleEvolutionaryAlgorithm.h"
#include "CartesianPoint.h"
#include "BuilderHelper.h"

#define CATCH_CONFIG_MAIN

int main(int argc, char* argv[])  {
    BuilderHelper builderHelper;
    while (1) {
        std::shared_ptr<IEvolutionaryAlgorithm> algorithm = builderHelper.createAlgorithm();
        if (algorithm) {
            Runner runner(algorithm);
            auto population = runner.run();
            std::cout << "Current algorithm population: " << std::endl;
            for (auto element: population) {
                CartesianPoint point = static_cast<CartesianPoint&>(*element);
                std::cout << point << std::endl;
            }
            std::cout << std::endl << "End of population.";
        } else {
            break;
        }
    }
    return 0;
}

