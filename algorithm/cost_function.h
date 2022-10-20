#ifndef KERNALS_COST_FUNCTION_H
#define KERNALS_COST_FUNCTION_H

#include "../graphx/digraph.h"

/**
 * @param G graph representation of problem
 * @param solution analyzed solution
 * @return numerical value associated with given `solution` (path)
 */
int costFunction(DiGraph& G, std::vector<int> solution) {
    int cost = 0;
    for (int i = 0; i < solution.size() - 1; i++)
        cost += G.getEdgeWeight(solution[i], solution[i+1]);
    return cost;
}

#endif //KERNALS_COST_FUNCTION_H
