#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include "Permutations.h"

int GetPathLength(std::vector<std::vector<int>> distanceMtx, const std::vector<int>& path, bool zeroIsNotEdge = true) {
	if (distanceMtx.empty() || path.empty()) {
		throw std::invalid_argument("Matrix and path cannot be empty");
	}
	if (distanceMtx.size() == 1) {
		return 0;
	}
	int length = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		if (distanceMtx[path[i]][path[i + 1]] == 0 && zeroIsNotEdge) {
			return std::numeric_limits<int>::max();
		}
		length += distanceMtx[path[i]][path[i + 1]];
	}
	if (distanceMtx[path[path.size() - 1]][path[0]] == 0 && zeroIsNotEdge) {
		return std::numeric_limits<int>::max();
	}
	length += distanceMtx[path[path.size() - 1]][path[0]];
	return length;
}

int FindShortestPath(const std::vector<std::vector<int>>& distanceMtx, std::vector<int>& path, bool zeroIsNotEdge = true) {
	if (distanceMtx.empty() || path.empty()) {
		throw std::invalid_argument("Matrix and path cannot be empty");
	}
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
		int length = GetPathLength(distanceMtx, tempPath, zeroIsNotEdge);
		if (length < minLength) {
			minLength = length;
			maxPath = tempPath;
		}
	} while (Permutations::Next(tempPath));
	path = maxPath;
	return minLength;
}