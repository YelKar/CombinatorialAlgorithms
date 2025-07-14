#pragma once
#include <vector>

namespace PermutationWithRepetition {

	bool Next(int *array, int n, int k) {
		if (n < 1 || k < 1) {
			throw std::invalid_argument("`n` and `k` must be positive");
		}
		if (std::any_of(array, array + k, [n](auto elt){return elt >= n || elt < 0; })) {
			throw std::invalid_argument("All elements must be less than `n`");
		}
		int i = 0;
		for (;array[i] == n - 1 && i < k; i++) {
			array[i] = 0;
		}
		if (i == k) {
			return false;
		}
		array[i]++;
		return true;
	}
	bool Next(std::vector<int> &array, int n) {
		if (array.empty()) {
			throw std::invalid_argument("Permutations cannot be empty");
		}
		return Next(array.data(), n, array.size());
	}
}