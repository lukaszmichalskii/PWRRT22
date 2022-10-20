import copy
import os
import pathlib
from typing import Tuple, List

from networkx import DiGraph


def load(file: pathlib.Path) -> Tuple[DiGraph, int, int]:
    edges = []
    with open(file, "r") as f:
        line = f.readline().split()
        V, E, src, dest = int(line[0]), int(line[1]), int(line[2]), int(line[3])
        for _ in range(E):
            data = f.readline().split()
            edges.append((int(data[0]), int(data[1]), {"weight": 0}))
            edges.append((int(data[1]), int(data[0]), {"weight": 1}))
    G = DiGraph()
    G.add_nodes_from([v for v in range(1, V + 1)])
    G.add_edges_from(edges)
    return G, src, dest


def cost_function(G: DiGraph, solution: List[int]) -> int:
    cost = 0
    for i in range(len(solution) - 1):
        cost += G.get_edge_data(solution[i], solution[i + 1]).get("weight")
    return cost


def backtracking(
    G: DiGraph, path: List[int], optimum: List[int], _min: float, dest: int
) -> Tuple[List[int], float]:
    V = path[-1]
    if len(path) == len(G.nodes):
        if not dest in G.neighbors(V):
            return optimum, _min  # dead end
        cost = cost_function(G, path)
        if cost < _min:
            _min = cost
            optimum = path
        return optimum, _min

    if V == dest:
        cost = cost_function(G, path)
        if cost == 0:
            _min = cost
            optimum = path
            return optimum, _min
        elif cost < _min:
            _min = cost
            optimum = path

    for neighbour in G.neighbors(V):
        if neighbour in path:
            continue
        np = copy.copy(path)  # shallow copy
        np.append(neighbour)
        if cost_function(G, np) >= _min:
            return optimum, _min
        optimum, _min = backtracking(G, np, optimum, _min, dest)
        del np
        if _min == 0:
            break
    return optimum, _min


def tkp(G: DiGraph, S: int, D: int) -> Tuple[List[int], float]:
    _min, optimum = float("inf"), []
    return backtracking(G, [S], optimum, _min, D)


if __name__ == "__main__":
    PoC = pathlib.Path(os.path.dirname(os.path.abspath(__file__)))
    file = PoC.joinpath("input.txt")
    f = pathlib.Path(file)
    G, src, dest = load(f)
    p, m = tkp(G, src, dest)
    print(p, m)
