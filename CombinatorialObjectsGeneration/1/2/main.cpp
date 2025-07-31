#include <algorithm>
#include "timer.h"
#include "print.h"
#include "matrix.h"
#include "TravelingSalesman.h"
#include <algorithm>

bool ProcessArgs(int argc, char *argv[], int &countOfPoints, std::vector<std::vector<int>> &distanceMtx);

int main(int argc, char *argv[]) {
	//	int countOfPoints = 0;
	//	std::vector<std::vector<int>> distanceMtx;
	//
	//	if (!ProcessArgs(argc, argv, countOfPoints, distanceMtx)) {
	//		return 1;
	//	}
	//
	//	std::cout << "Cities:" << std::endl;
	//	tools::PrintMatrix(distanceMtx);
	//
	//	std::vector<int> path(countOfPoints);
	//	std::iota(path.begin(), path.end(), 0);
	//
	//	int length;
	//	auto time = tools::Timer::Measure([&length, distanceMtx, &path] {
	//		length = FindShortestPath(distanceMtx, path);
	//	});
	//
	//	std::cout << "Path length: " << length << std::endl;
	//	std::cout << "path: ";
	//	tools::PrintArray(path);
	//	std::cout << "Time: " << time.ToSeconds() << "s" << std::endl;

	std::vector<std::vector<int>> mtx{
				{0, 8, 1, 0, 3, 0},
				{8, 0, 6, 5, 0, 0},
				{1, 6, 0, 4, 5, 0},
				{0, 5, 4, 0, 6, 4},
				{3, 0, 5, 6, 0, 7},
				{0, 0, 0, 4, 7, 0},
	};

	// std::vector<std::vector<int>> mtx{
	// 			{0, 1, 2},
	// 			{1, 0, 3},
	// 			{2, 3, 0},
	// };
	std::vector<int> path(mtx.size());
	auto l = FindShortestPath(mtx, path);
	std::transform(path.begin(), path.end(), path.begin(), [](auto v) {
		return v + 1;
	});
	tools::PrintArray(path);
	std::cout << l << std::endl;
	return 0;
}


bool ProcessArgs(int argc, char *argv[], int &countOfPoints, std::vector<std::vector<int>> &distanceMtx) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <count of cities> <volume matrix file>" << std::endl;
		return false;
	} else {
		countOfPoints = std::stoi(argv[1]);
		tools::ParseMatrix(argv[2], distanceMtx);
	}
	if (distanceMtx.size() < countOfPoints) {
		std::cerr << "Error: distanceMtx must have " << countOfPoints << " rows or more" << std::endl;
		return false;
	}

	distanceMtx.resize(countOfPoints);
	for (int i = 0; i < countOfPoints; i++) {
		distanceMtx[i].resize(countOfPoints);
	}
	return true;
}


