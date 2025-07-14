#include <gtest/gtest.h>
#include <cmath>
#include "Combinations.h"

using namespace Combinations;

TEST(CombinationsValidation, ThrowsOnZero) {
	std::vector<int> empty;
	EXPECT_THROW(First(0, 0), std::invalid_argument);
	EXPECT_THROW(Next(empty, 0), std::invalid_argument);
}

TEST(CombinationsValidation, ThrowsOnUnsuitableElement) {
	std::vector<int> arr = {1, 2, 10};
	EXPECT_THROW(Next(arr, 4), std::invalid_argument);
	arr = {1, 2, 0};
	EXPECT_THROW(Next(arr, 4), std::invalid_argument);
}

TEST(CombinationsValidation, ThrowsRepetition) {
	std::vector<int> arr = {1, 2, 3, 4, 4};
	EXPECT_THROW(Next(arr, 4), std::invalid_argument);
}

TEST(CombinationsValidation, ThrowsTooBigCombinationSize) {
	EXPECT_THROW(First(5, 10), std::invalid_argument);
}

class CombinationCountTest : public ::testing::TestWithParam<std::tuple<int, int>> {};

int EstimateCountOfCombinations(int n, int k) {
	return std::round(
		std::tgamma(n + 1)
		/ (std::tgamma(k + 1) * std::tgamma(n - k + 1))
	);
}

TEST_P(CombinationCountTest, CountOfCombinations) {
	auto [n, k] = GetParam();

	std::vector<int> arr;
	EXPECT_NO_THROW(arr = First(n, k));

	int count = 1;
	while (Next(arr, n)) count++;

	int expected = EstimateCountOfCombinations(n, k);
	EXPECT_EQ(count, expected);
}

TEST_P(CombinationCountTest, LastCombination) {
	auto [n, k] = GetParam();

	std::vector<int> arr;
	EXPECT_NO_THROW(arr = First(n, k));
	while (Next(arr, n));
	std::vector<int> expected(arr.size());
	std::iota(expected.begin(), expected.end(), n - k + 1);
	EXPECT_EQ(arr, expected);
}

INSTANTIATE_TEST_SUITE_P(
	Cases,
	CombinationCountTest,
	::testing::Values(
		std::tuple{2, 1},
		std::tuple{20, 1},
		std::tuple{20, 10},
		std::tuple{7, 5},
		std::tuple{9, 3},
		std::tuple{9, 9},
		std::tuple{1, 1}
	)
);


