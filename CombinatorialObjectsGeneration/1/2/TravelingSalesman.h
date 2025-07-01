#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>

int GetPathLength(std::vector<std::vector<int>> distanceMtx, const std::vector<int>& path) {
	int length = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		length += distanceMtx[path[i]][path[i + 1]];
	}
	length += distanceMtx[path[path.size() - 1]][path[0]];
	return length;
}

int FindShortestPath(std::vector<std::vector<int>> distanceMtx, std::vector<int>& path) {
	if (distanceMtx.size() != path.size()) {
		throw std::invalid_argument("distanceMtx and path must have the same size");
	}
	path.clear();
	path.resize(distanceMtx.size());
	for (int i = 0; i < distanceMtx.size(); path[i++] = i);
	int minLength = std::numeric_limits<int>::max();
	std::vector<int> tempPath(path);
	std::vector<int> maxPath(path);
	do {
		int length = GetPathLength(distanceMtx, tempPath);
		if (length < minLength) {
			minLength = length;
			maxPath = tempPath;
		}
	} while (std::next_permutation(tempPath.begin(), tempPath.end()));
	path = maxPath;
	return minLength;
}