#include <vector>
#include <thread>
#include "PermutationWithRepetition.h"
#include <chrono>
#include <thread>

bool IsCorrectColors(const std::vector<std::vector<int>>& adjacencyMtx, const std::vector<int>& colors) {
    auto size = colors.size();
    for (int i = 0; i < size; i++) {
        int vertexColor = colors[i];
        for (int j = 0; j < size; j++) {
            if (adjacencyMtx[i][j] && vertexColor == colors[j])
                return false;
        }
    }

    return true;
}

std::vector<int> ColorGraph(const std::vector<std::vector<int>>& adjacencyMtx) {
	auto size = adjacencyMtx.size();
	for (int i = 1; i < size; i++) {
		std::vector<int> colors(adjacencyMtx.size(), 0);
		do {
			if (IsCorrectColors(adjacencyMtx, colors))
				return colors;
		} while (PermutationWithRepetition::Next(colors, i));
		std::cout << std::endl;
	}
    return {};
}
