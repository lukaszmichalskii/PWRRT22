#include "digraph.h"

void DiGraph::addFromEdges(int V, const std::vector<Edge> &edges) {
    this->initList(V, edges);
}

void DiGraph::initList(int V, const std::vector<Edge> &edges) {
    for (int i = 1; i < V+1; i++) {
        std::vector<std::pair<int, int>> v;
        this->adjList[i] = v;
    }

    for (Edge edge: edges)
        this->adjList[edge.src].push_back(std::make_pair(edge.dest, edge.weight));
}

int DiGraph::getEdgeWeight(int src, int dest) {
    for (auto & it : this->adjList[src])
        if (it.first == dest)
            return it.second;
    return -1;
}

std::vector<int> DiGraph::neighbours(int V) {
    std::vector<int> n;
    for (auto & it : this->adjList[V])
        n.push_back(it.first);
    return n;
}

std::vector<int> DiGraph::nodes() {
    std::vector<int> _nodes;
    for(auto & it : this->adjList)
        _nodes.push_back(it.first);
    return _nodes;
}
