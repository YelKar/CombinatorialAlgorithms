#include <algorithm>
#include "timer.h"
#include "print.h"
#include "matrix.h"
#include "TravelingSalesman.h"

int main(int argc, char *argv[]) {
	tools::Timer timer;
	int countOfPoints = 0;
	std::vector<std::vector<int>> distanceMtx;

	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <count of cities> <volume matrix file>" << std::endl;
		return 1;
	} else {
		countOfPoints = atoi(argv[1]);
		tools::ParseMatrix(argv[2], distanceMtx);
	}
	if (distanceMtx.size() < countOfPoints) {
		std::cerr << "Error: distanceMtx must have " << countOfPoints << " rows or more" << std::endl;
		return 1;
	}

	distanceMtx.resize(countOfPoints);
	for (int i = 0; i < countOfPoints; i++) {
		distanceMtx[i].resize(countOfPoints);
	}

	std::cout << "Cities:" << std::endl;
	tools::PrintMatrix(distanceMtx);


	std::vector<int> path = {};
	for (int i = 0; i < countOfPoints; i++) {
		path.push_back(i);
	}
	int length = FindShortestPath(distanceMtx, path);
	std::cout << "Path length: " << length << std::endl;
	std::cout << "path: ";
	tools::PrintArray(path);
	std::cout << std::endl;
	return 0;
}

