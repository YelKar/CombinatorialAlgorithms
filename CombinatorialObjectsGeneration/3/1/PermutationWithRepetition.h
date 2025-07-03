#include <vector>

namespace PermutationWithRepetition {
	std::vector<int> First(int n, int k) {
		std::vector<int> array(k, 0);
		return array;
	}

	bool Next(int *array, int n, int k) {
		int i = 0;
		for (;array[i] == n - 1; i++) {
			array[i] = 0;
		}
		if (i == k) {
			return false;
		}
		array[i]++;
		return true;
	}
	bool Next(std::vector<int> &array, int n) {
		return Next(array.data(), n, array.size());
	}
}