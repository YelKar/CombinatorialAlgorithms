#include <vector>
#include "print.h"
#include "timer.h"
#include "matrix.h"
#include "GraphColoring.h"


bool ProcessArgs(int argc, char **argv, int &countOfPoints, std::vector<std::vector<int>> &adjacencyMtx);

int main(int argc, char** argv) {
	int countOfPoints = 0;
	std::vector<std::vector<int>> adjacencyMtx;

	if (!ProcessArgs(argc, argv, countOfPoints, adjacencyMtx)) {
		return 1;
	}

	std::cout << "Adjacency Matrix:" << std::endl;
	tools::PrintMatrix(adjacencyMtx);
	std::vector<int> colors;
	auto time = tools::Timer::Measure([&colors, &adjacencyMtx] {
		colors = ColorGraph(adjacencyMtx);
	});
	std::cout << "Colors (" << *std::max_element(colors.begin(), colors.end()) + 1 << "):" << std::endl;
	tools::PrintArray(colors);
	std::cout << "Time: " << time.ToSeconds() << "s" << std::endl;

	return 0;
}

bool ProcessArgs(int argc, char **argv, int &countOfPoints, std::vector<std::vector<int>> &adjacencyMtx) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <count of vertexes> <matrix file>" << std::endl;
		return false;
	} else {
		countOfPoints = std::stoi(argv[1]);
		tools::ParseMatrix(argv[2], adjacencyMtx);
	}
	if (adjacencyMtx.size() < countOfPoints) {
		std::cerr << "Error: distanceMtx must have " << countOfPoints << " rows or more" << std::endl;
		return false;
	}

	adjacencyMtx.resize(countOfPoints);
	for (int i = 0; i < countOfPoints; i++) {
		adjacencyMtx[i].resize(countOfPoints);
	}
	return true;
}

