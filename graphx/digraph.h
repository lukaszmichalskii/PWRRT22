#ifndef KERNALS_DIGRAPH_H
#define KERNALS_DIGRAPH_H


#include <map>
#include <vector>
#include "edge.h"

class DiGraph {
private:
    std::map<int, std::vector<std::pair<int,int>>> adjList;
    std::vector<std::vector<int>> adjMatrix;
    void initList(int V, const std::vector<Edge>& edges);
public:
    void addFromEdges(int V, const std::vector<Edge>& edges);
    int getEdgeWeight(int src, int dest);
    std::vector<int> neighbours(int V);
    std::vector<int> nodes();
    DiGraph() = default;
};


#endif //KERNALS_DIGRAPH_H
