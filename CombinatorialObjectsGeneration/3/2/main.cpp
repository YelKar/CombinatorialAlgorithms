#include <vector>
#include "print.h"
#include "timer.h"
#include "matrix.h"
#include "GraphColoring.h"

int main(int argc, char** argv) {
	tools::Timer timer;
	int countOfPoints = 0;
	std::vector<std::vector<int>> adjacencyMtx;

	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <count of vertexes> <matrix file>" << std::endl;
		return 1;
	} else {
		countOfPoints = std::stoi(argv[1]);
		tools::ParseMatrix(argv[2], adjacencyMtx);
	}
	if (adjacencyMtx.size() < countOfPoints) {
		std::cerr << "Error: distanceMtx must have " << countOfPoints << " rows or more" << std::endl;
		return 1;
	}

	adjacencyMtx.resize(countOfPoints);
	for (int i = 0; i < countOfPoints; i++) {
		adjacencyMtx[i].resize(countOfPoints);
	}

	std::cout << "Adjacency Matrix:" << std::endl;
	tools::PrintMatrix(adjacencyMtx);

	timer.Start();
	auto colors = ColorGraph(adjacencyMtx);
	auto time = timer.GetDelta();
	std::cout << "Colors (" << *std::max_element(colors.begin(), colors.end()) + 1 << "):" << std::endl;
	tools::PrintArray(colors);
	std::cout << "Time: " << time.ToSeconds() << "s" << std::endl;

	return 0;
}