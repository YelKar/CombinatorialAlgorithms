#include <gtest/gtest.h>
#include "TravelingSalesman.h"
#include <cmath>
#include <ranges>

class TSTest : public ::testing::TestWithParam<std::tuple<std::vector<std::vector<int>>, int>> {};

TEST_P(TSTest, Tests) {
	auto [mtx, expected] = GetParam();
	std::vector<int> path(mtx.size());
	auto length = FindShortestPath(mtx, path);
	EXPECT_EQ(length, expected);
}

INSTANTIATE_TEST_SUITE_P(
	Cases,
	TSTest,
	::testing::Values(
		std::make_tuple(
			std::vector<std::vector<int>>{
				{0, 1, 2},
				{1, 0, 3},
				{2, 3, 0}
			},
			6
		),
		std::make_tuple(
			std::vector<std::vector<int>>{
				{0, 1, 1},
				{1, 0, 1},
				{1, 1, 0}
			},
			3
		),
		std::make_tuple(
			std::vector<std::vector<int>>{
				{0}
			},
			0
		),
		std::make_tuple(
			std::vector<std::vector<int>>{
				{0, 1, 100, 1},
				{1, 0, 1, 100},
				{100, 1, 0, 1},
				{1, 100, 1, 0}
			},
			4
		),
		std::make_tuple(
			std::vector<std::vector<int>>{
				{0, 1, 2},
				{3, 0, 4},
				{5, 6, 0}
			},
			10
		),
		std::make_tuple(
			std::vector<std::vector<int>>{
				{0, 1, 1, 1000},
				{1, 0, 1, 1},
				{1, 1, 0, 1},
				{1000, 1, 1, 0}
			},
			4
		),
		std::make_tuple(
			std::vector<std::vector<int>>{
				{ 0, 8, 0, 0, 0, 0, 0, 4, 0 },
				{ 8, 0, 2, 0, 0, 0, 0, 0, 0 },
				{ 0, 2, 0, 1, 0, 0, 0, 0, 1 },
				{ 0, 0, 1, 0, 2, 0, 0, 0, 0 },
				{ 0, 0, 0, 2, 0, 1, 1, 0, 0 },
				{ 0, 0, 0, 0, 1, 0, 100, 0, 0 },
				{ 0, 0, 0, 0, 1, 100, 0, 1, 1 },
				{ 4, 0, 0, 0, 0, 0, 1, 0, 1 },
				{ 0, 0, 1, 0, 0, 0, 1, 1, 0 },
			},
			120
		),
		std::make_tuple(
			std::vector<std::vector<int>>{
				{0, 1, 1, 1},
				{1, 0, 2, 2},
				{1, 2, 0, 2},
				{1, 2, 2, 0}
			},
			6
		),
		std::make_tuple(
			std::vector<std::vector<int>>{
				{0, 5, 4, 10},
				{5, 0, 6, 5},
				{4, 6, 0, 4},
				{10, 5, 4, 0}
			},
			18
		),
		std::make_tuple(
			std::vector<std::vector<int>>{
				{0, 100, 1, 1},
				{100, 0, 300, 400},
				{1, 300, 0, 500},
				{1, 400, 500, 0}
			},
			702
		),
		std::make_tuple(
			std::vector<std::vector<int>>{
				{0, 1, 3, 2},
				{1, 0, 1, 3},
				{3, 1, 0, 1},
				{2, 3, 1, 0}
			},
			5
		)
	)
);
