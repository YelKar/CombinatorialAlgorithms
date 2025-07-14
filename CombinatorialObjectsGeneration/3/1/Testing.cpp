#include <gtest/gtest.h>
#include <cmath>
#include "PermutationWithRepetition.h"

using namespace PermutationWithRepetition;

TEST(PermutationsValidation, ThrowsOnZero) {
	std::vector<int> empty;
	std::vector<int> nonempty{1, 2, 3};
	EXPECT_THROW(Next(empty, 1), std::invalid_argument);
	EXPECT_THROW(Next(nonempty, 0), std::invalid_argument);
}

TEST(PermutationsValidation, ThrowsOnUnsuitableElement) {
	std::vector<int> withUnsuitableElt{1, 2, 10};
	EXPECT_THROW(Next(withUnsuitableElt, 5), std::invalid_argument);
}

class PermutationCountTest : public ::testing::TestWithParam<std::tuple<int, int>> {};

int EstimateCountOfPermutations(int n, int k) {
	return std::pow(n, k);
}

TEST_P(PermutationCountTest, CountOfPermutations) {
	auto [n, k] = GetParam();

	std::vector<int> arr(k, 0);

	int count = 1;
	while (Next(arr, n)) count++;

	int expected = EstimateCountOfPermutations(n, k);
	EXPECT_EQ(count, expected);
}

TEST_P(PermutationCountTest, LastPermutation) {
	auto [n, k] = GetParam();

	std::vector<int> arr(k, 0);
	std::vector<int> last;
	do
		last = arr;
	while (Next(arr, n));

	std::vector<int> expected(k, n - 1);
	EXPECT_EQ(last, expected);
}

INSTANTIATE_TEST_SUITE_P(
	Cases,
	PermutationCountTest,
	::testing::Values(
		std::tuple{2, 1},
		std::tuple{20, 1},
		std::tuple{7, 5},
		std::tuple{9, 3},
		std::tuple{9, 9},
		std::tuple{1, 1}
	)
);


