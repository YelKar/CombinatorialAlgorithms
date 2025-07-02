#pragma once
#include <vector>
#include <numeric>

namespace Combinations {

bool Next(std::vector<int>& array, int n) {
	int k = array.size();

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
	std::vector<int> array(k);
	std::iota(array.begin(), array.end(), 1);
	return array;
}

}