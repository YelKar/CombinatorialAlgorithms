#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

namespace Permutations
{
	std::vector<int> First(int n)
	{
		if (n == 0) {
			throw std::invalid_argument("Permutation must have positive length");
		}

		std::vector<int> result(n);
		std::iota(result.begin(), result.end(), 1);
		return result;
	}

	bool Next(int *array, std::size_t size)
	{
		if (size == 0) {
			throw std::invalid_argument("Permutation must have positive length");
		}
		std::size_t i = size - 1;
		for (; i > 0 && array[i - 1] >= array[i]; i--);
		if (i == 0)
		{
			return false;
		}
		std::size_t j = size - 1;
		for (; array[i - 1] >= array[j]; j--);
		std::swap(array[i - 1], array[j]);
		std::reverse(array + i, array + size);
		return true;
	}

	bool Next(std::vector<int> &array)
	{
		return Next(array.data(), array.size());
	}
}