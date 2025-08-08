#include <iostream>
#include "Digraph.h"
#include "print.h"

int main(int argc, char **argv) {
    Digraph graph{
                {1, 2}, {2, 3}, {3, 1},
                {4, 5}, {5, 6}, {6, 4},
                {4, 1}
            };

    // Алгоритм Тарьяна
    for (const auto &connectedComponent : graph.getConnectedComponents()) {
        tools::PrintArray(std::vector<IdType>(connectedComponent.begin(), connectedComponent.end()));
    }
    auto cond = graph.Condensation();
    tools::PrintArray(cond.getNodes());
    tools::PrintArray(cond.getEdges());
    std::set<std::set<IdType>> components;
    return 0;
}