#pragma once
#include <vector>
#include <numeric>
#include <set>

namespace Combinations {

void ValidateCombination(const std::vector<int>& array, int n) {
	if (array.size() == 0) {
		throw std::invalid_argument("combination size cannot be zero");
	}
	if (array.size() != std::set<int>(array.begin(), array.end()).size()) {
		throw std::invalid_argument("combination elements cannot repeat");
	}
	for (int i : array) {
		if (i < 1) {
			throw std::invalid_argument("combination elements must be 0 or greater");
		} else if (i > n) {
			throw std::invalid_argument("combination elements must be less or equal to `n`");
		}
	}
}

bool Next(std::vector<int>& array, int n) {
	ValidateCombination(array, n);

	int k = static_cast<int>(array.size());

	int i = k - 1;
	for (;i >= 0 && array[i] == n - k + i + 1; --i);

	if (i < 0) {
		return false;
	}
	++array[i];

	for (int j = i + 1; j < k; ++j) {
		array[j] = array[j - 1] + 1;
	}

	return true;
}

std::vector<int> First(int n, int k) {
	if (k == 0) {
		throw std::invalid_argument("combination size cannot be zero");
	}
	if (n < k) {
		throw std::invalid_argument("combination size must be less or equal to `n`");
	}
	std::vector<int> array(k);
	std::iota(array.begin(), array.end(), 1);
	return array;
}

}