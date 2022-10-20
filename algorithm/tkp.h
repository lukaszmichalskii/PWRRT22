//
// Created by lukas on 20/10/2022.
//

#ifndef KERNALS_TKP_H
#define KERNALS_TKP_H

#include <vector>
#include <climits>
#include "../graphx/digraph.h"
#include "backtracking.h"

/**
 * tkp() wrapper for travelling kruskal problem
 * @param G graph representation of problem
 * @param src starting point
 * @param dest goal
 * @return :
 *      optimum = proposed minimum cost path
 *      _min = integer minimum value associated to path from `src`->`dest` based on problem specifications, -1 is not existing
 */
std::pair<std::vector<int>, int> tkp(const DiGraph& G, int &src, int &dest) {
    int _min = INT_MAX;
    std::vector<int> optimum;
    std::vector<int> initialPath = {src};
    std::tie(optimum, _min) = backtracking(G, initialPath, optimum, _min, dest);
    if (optimum.empty())
        return std::make_pair(optimum, -1);
    return std::make_pair(optimum, _min);
}

#endif //KERNALS_TKP_H
