#include <iostream>
#include "Digraph.h"
#include "print.h"

int main(int argc, char **argv) {
    Digraph graph{
        {1, 4}, {1, 6}, {2, 1}, {2, 7}, {3, 2},
        {3, 5}, {3, 8}, {4, 2}, {4, 6}, {4, 7},
        {5, 3}, {5, 8}, {6, 4}, {6, 9}, {8, 9},
        {8, 10}, {9, 7}, {10, 11}, {11, 8}, {12, 14},
        {12, 15}, {14, 15}
    };

    // Алгоритм Тарьяна
    for (const auto &connectedComponent : graph.getConnectedComponents()) {
        tools::PrintArray(std::vector<IdType>(connectedComponent.begin(), connectedComponent.end()));
    }
    std::set<std::set<IdType>> components;
    return 0;
}