//
// Created by lukas on 20/10/2022.
//

#ifndef KERNALS_BACKTRACKING_H
#define KERNALS_BACKTRACKING_H

#include <vector>
#include "utilities.h"
#include "../graphx/digraph.h"
#include "cost_function.h"

/**
 * Using backtracking and branch & bound technique
 * finds global `_min` value associated with optimal path for problem
 * @param G Directed graph representation of problem
 * @param path currently explored path
 * @param optimum current optimal path
 * @param _min current optimal solution
 * @param dest destination of travel
 * @return
 */
std::pair<std::vector<int>, int> backtracking(DiGraph G,
                                              std::vector<int>& path,
                                              std::vector<int>& optimum,
                                              int& _min,
                                              int& dest) {
    int V = path.back();
    if (path.size() == G.nodes().size()) { // avoid cycles
        if (!contains(path, dest))
            return std::make_pair(optimum, _min);
        int cost = costFunction(G, path);
        if (cost < _min) {
            _min = cost;
            optimum = path;
        }
        return std::make_pair(optimum, _min);
    }

    if (V == dest) { // find possible solution
        int cost = costFunction(G, path);
        if (cost == 0) { // lower bound limitation, no need to search for better solution
            _min = cost;
            optimum = path;
            return std::make_pair(optimum, _min);
        }
        if (cost < _min) { // find local optimal solution
            _min = cost;
            optimum = path;
        }
    }

    std::vector<int> neighbours = G.neighbours(V);
    for (int neighbour: neighbours) {
        if (contains(path, neighbour))
            continue;
        std::vector<int> explored = path;
        explored.push_back(neighbour);
        int cost = costFunction(G, explored);
        if (cost >= _min) // upper bound limitation: do not explore, reduce solution space
            return std::make_pair(optimum, _min);
        std::tie(optimum, _min) = backtracking(G, explored, optimum, _min, dest);
        explored.clear();
        explored.shrink_to_fit();
        if (_min == 0) // lower bound limitation, no need to search for better solution
            break;
    }
    return std::make_pair(optimum, _min);
}

#endif //KERNALS_BACKTRACKING_H
