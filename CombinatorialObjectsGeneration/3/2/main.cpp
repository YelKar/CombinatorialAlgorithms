#include <iostream>
#include "GraphColoring.h"

int main() {
	Graph faces = {
		{{0, 1}, {1, 2}, {2, 0}},
		{{0, 2}, {2, 3}, {3, 0}},
		{{0, 3}, {3, 4}, {4, 0}},
		{{0, 4}, {4, 5}, {5, 0}},
		{{0, 5}, {5, 1}, {1, 0}},
		{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 1}},
	};

	DualGraph dual = BuildDualGraph(faces);

	std::vector<int> coloring;
	if (GraphColoring(dual, coloring)) {
		std::cout << "Минимальная раскраска: " << std::endl;
		for (int i = 0; i < coloring.size(); ++i) {
			std::cout << "Грань " << i << " → Цвет " << coloring[i] << std::endl;
		}
	} else {
		std::cout << "Не удалось раскрасить граф" << std::endl;
	}

	return 0;
}
