#include <fstream>
#include <sstream>
#include <iostream>
#include "graphx/digraph.h"
#include "algorithm/tkp.h"

class ArgumentParserError : public std::exception {
private:
    std::string _msg = "Error while initializing problem.";
public:
    ArgumentParserError()= default;
    const char* what() const noexcept override {
        return _msg.c_str();
    }
};

class FileReadError : public std::exception {
private:
    std::string _msg = "Error while loading problem instance.\nProvide absolute filepath to input file.";
public:
    FileReadError()= default;
    const char* what() const noexcept override {
        return _msg.c_str();
    }
};

std::pair<int, int> loadProblem(DiGraph& G, const std::string& absFilepath) {
    std::string buffer;
    std::vector<Edge> edgesList;
    std::ifstream file(absFilepath);
    try {
        int V = -1, E = -1, src = -1, dest = -1, v1 = -1, v2 = -1;
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        getline(file, buffer, '\n');
        ss << buffer;
        ss >> V >> E >> src >> dest;
        if (V == -1 or E == -1 or src == -1 or dest == -1)
            throw FileReadError();
        for (int i = 0; i < E; i++) {
            getline(file, buffer, '\n');
            ss << buffer;
            ss >> v1 >> v2;
            edgesList.emplace_back(v1, v2, 0);
            edgesList.emplace_back(v2, v1, 1);
        }

        file.close();

        G.addFromEdges(V, edgesList);
        return std::make_pair(src, dest);
    } catch (...) {
        throw FileReadError();
    }
}

void parseArgs(int argc, char *argv[]) {
    if (argc != 2)
        throw ArgumentParserError();
}

void print(int _min, const std::vector<int>& proposed_path) {
    std::cout << "Min: " << _min << std::endl;
    int i = 0;
    if (proposed_path.empty()) {
        std::cout << "Path: []" << std::endl;
        return;
    }
    std::cout << "Path: [";
    for (int v: proposed_path) {
        if (i == 0) {
            std::cout << v;
            i++;
            continue;
        }
        std::cout << " -> " << v;
    }
    std::cout << "]" << std::endl;
}

int main(int argc, char *argv[]) {
    parseArgs(argc, argv);
    DiGraph G = DiGraph();
    int src, dest, _min;
    std::vector<int> path;
    std::string absFilepath = argv[1];
    std::tie(src, dest) = loadProblem(G, absFilepath);
    std::tie(path, _min) = tkp(G, src, dest);
    print(_min, path);
    return 0;
}
