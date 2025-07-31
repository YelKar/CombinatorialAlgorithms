#include <gtest/gtest.h>
#include "GeometricGraph.h"
#include <cmath>
#include <ranges>
#include "print.h"

using Matrix = GeometricGraph::AdjacencyMatrix;

class TSTest : public ::testing::TestWithParam<std::tuple<Matrix, double>> {};

TEST_P(TSTest, Tests) {
	auto [mtx, expected] = GetParam();
	auto path = GeometricGraph::HamiltonianCycle(mtx);
	auto length = GeometricGraph::GetLength(mtx, path);
	EXPECT_EQ(length, expected) << tools::RenderArray(path).str();
}

const double Inf = GeometricGraph::INF;

INSTANTIATE_TEST_SUITE_P(
	Cases,
	TSTest,
	::testing::Values(
		std::make_tuple(
			Matrix{
				{Inf, 1, 2},
				{1, Inf, 3},
				{2, 3, Inf}
			},
			6
		),
		std::make_tuple(
			Matrix{
				{Inf, 1, 1},
				{1, Inf, 1},
				{1, 1, Inf}
			},
			3
		),
		std::make_tuple(
			Matrix{
				{Inf}
			},
			0
		),
		std::make_tuple(
			Matrix{
				{Inf, 1, 100, 1},
				{1, Inf, 1, 100},
				{100, 1, Inf, 1},
				{1, 100, 1, Inf}
			},
			4
		),
		std::make_tuple(
			Matrix{
				{Inf, 1, 2},
				{3, Inf, 4},
				{5, 6, Inf}
			},
			10
		),
		std::make_tuple(
			Matrix{
				{Inf, 1, 1, 1000},
				{1, Inf, 1, 1},
				{1, 1, Inf, 1},
				{1000, 1, 1, Inf}
			},
			4
		),
		std::make_tuple(
			Matrix{
				{ Inf, 8, Inf, Inf, Inf, Inf, Inf, 4, Inf },
				{ 8, Inf, 2, Inf, Inf, Inf, Inf, Inf, Inf },
				{ Inf, 2, Inf, 1, Inf, Inf, Inf, Inf, 1 },
				{ Inf, Inf, 1, Inf, 2, Inf, Inf, Inf, Inf },
				{ Inf, Inf, Inf, 2, Inf, 1, 1, Inf, Inf },
				{ Inf, Inf, Inf, Inf, 1, Inf, 100, Inf, Inf },
				{ Inf, Inf, Inf, Inf, 1, 100, Inf, 1, 1 },
				{ 4, Inf, Inf, Inf, Inf, Inf, 1, Inf, 1 },
				{ Inf, Inf, 1, Inf, Inf, Inf, 1, 1, Inf },
			},
			120
		),
		std::make_tuple(
			Matrix{
				{Inf, 1, 1, 1},
				{1, Inf, 2, 2},
				{1, 2, Inf, 2},
				{1, 2, 2, Inf}
			},
			6
		),
		std::make_tuple(
			Matrix{
				{Inf, 5, 4, 10},
				{5, Inf, 6, 5},
				{4, 6, Inf, 4},
				{10, 5, 4, Inf}
			},
			18
		),
		std::make_tuple(
			Matrix{
				{Inf, 100, 1, 1},
				{100, Inf, 300, 400},
				{1, 300, Inf, 500},
				{1, 400, 500, Inf}
			},
			702
		),
		std::make_tuple(
			Matrix{
				{Inf, 1, 3, 2},
				{1, Inf, 1, 3},
				{3, 1, Inf, 1},
				{2, 3, 1, Inf}
			},
			5
		)
	)
);
