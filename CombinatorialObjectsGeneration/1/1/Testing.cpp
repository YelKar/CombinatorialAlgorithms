#include <gtest/gtest.h>
#include "Permutations.h"
#include <cmath>
#include <ranges>

using namespace Permutations;

TEST(PermutationsValidation, ThrowsOnZeroFirst)
{
	EXPECT_THROW(First(0), std::invalid_argument);
}

TEST(PermutationsValidation, ThrowsOnZeroNext)
{
	std::vector<int> empty;
	EXPECT_THROW(Next(empty), std::invalid_argument);
}


TEST(PermutationTest, NextProducesCorrectPermutation)
{
	std::vector<int> p = First(3);
	ASSERT_TRUE(Next(p));
	EXPECT_EQ(p, (std::vector<int>{1, 3, 2}));
}

TEST(PermutationTest, NextReturnsFalseOnLastPermutation)
{
	std::vector<int> p = {3, 2, 1};
	EXPECT_FALSE(Next(p));
	EXPECT_EQ(p, (std::vector<int>{3, 2, 1}));
}


class PermutationParamTest : public ::testing::TestWithParam<int> {};

TEST_P(PermutationParamTest, CountOfPermutations)
{
	int n = GetParam();
	std::vector<int> p = First(n);
	int count = 1;
	while (Next(p)) count++;
	EXPECT_EQ(count, std::tgamma(n + 1));
}

TEST_P(PermutationParamTest, ReversedLastPermutation)
{
	int n = GetParam();
	std::vector<int> p = First(n);
	std::vector<int> reversed = std::views::reverse(First(n)) | std::ranges::to<std::vector<int>>();
	while (Next(p));
	EXPECT_EQ(p, reversed) << "Expected last permutation to be reversed";
}

INSTANTIATE_TEST_SUITE_P(
	FirstSizes,
	PermutationParamTest,
	::testing::Values(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
);

TEST(PermutationFullCycle, AllPermutationsOfThree)
{
	std::vector<int> p = First(3);
	std::vector<std::vector<int>> expected = {
		{1, 2, 3},
		{1, 3, 2},
		{2, 1, 3},
		{2, 3, 1},
		{3, 1, 2},
		{3, 2, 1}
	};

	std::vector<std::vector<int>> generated;
	int step = 0;
	do {
		SCOPED_TRACE("Step #" + std::to_string(step));
		EXPECT_EQ(expected[step], p);
		generated.push_back(p);
		step++;
	} while (Next(p));

	EXPECT_EQ(generated, expected);
}

class SpecificTests : public ::testing::TestWithParam<std::vector<int>> {};

static int CountUniquePermutations(const std::vector<int>& array) {
	std::map<int, int> counts;
	for (int x : array)
		counts[x]++;

	auto total = std::tgamma(array.size() + 1);
	for (auto& [_, count] : counts)
		total /= std::tgamma(count + 1);
	return static_cast<int>(total);
}

TEST_P(SpecificTests, GeneratesCorrectPermutationCount)
{
	std::vector<int> input = GetParam();
	std::sort(input.begin(), input.end());

	std::vector<std::vector<int>> unique;
	do {
		unique.push_back(input);
	} while (Next(input));

	uint64_t expected = CountUniquePermutations(GetParam());
	EXPECT_EQ(unique.size(), expected)
					<< "Expected " << expected << " permutations, got " << unique.size();
}

TEST_P(SpecificTests, ReversedLastPermutation)
{
	std::vector<int> array = GetParam();
	std::sort(array.begin(), array.end());

	std::vector<int> reversed = std::views::reverse(array) | std::ranges::to<std::vector<int>>();
	while (Next(array));

	EXPECT_EQ(array, reversed) << "Expected last permutation to be reversed";
}

INSTANTIATE_TEST_SUITE_P(
	OtherPermutations,
	SpecificTests,
	::testing::Values(
		std::vector<int>{0, 1, 2},
		std::vector<int>{3, 4, 5},
		std::vector<int>{1, 6, 9},
		std::vector<int>{10, 20, 30},
		std::vector<int>{7},
		std::vector<int>{8, 9}
	)
);

INSTANTIATE_TEST_SUITE_P(
	PermutationsWithRepetition,
	SpecificTests,
	::testing::Values(
		std::vector<int>{5, 5, 5, 5, 6, 7},
		std::vector<int>{2, 2, 2},
		std::vector<int>{1, 1, 2},
		std::vector<int>{9, 9, 9, 10}
	)
);
