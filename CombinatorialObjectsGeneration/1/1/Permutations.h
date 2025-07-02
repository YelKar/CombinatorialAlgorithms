#pragma once

#include <vector>
#include <algorithm>

namespace Permutations
{

	bool Next(int *array, std::size_t size)
	{
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