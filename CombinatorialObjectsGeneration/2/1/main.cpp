#include <cmath>
#include "print.h"
#include "Combinations.h"

int EstimateCountOfCombinations(int n, int k) {
	return std::round(
		std::tgamma(n + 1)
		/ (std::tgamma(k + 1) * std::tgamma(n - k + 1))
	);
}

int main(int argc, char** argv) {
	auto array = Combinations::First(20, 1);
	do {
		tools::PrintArray(array);
	} while (Combinations::Next(array, 20));
	int a = EstimateCountOfCombinations(20, 1);
	std::cout << a << " " << std::endl;

	return 0;
}