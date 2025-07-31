#include <gtest/gtest.h>
#include "Digraph.h"


class TSTest : public ::testing::TestWithParam<std::tuple<std::initializer_list<DigraphEdge>, std::set<ConnectedComponent>>> {};

TEST_P(TSTest, Tests) {
	auto [edges, expected] = GetParam();
    Digraph graph(edges);
    auto actual = graph.getConnectedComponents();
    EXPECT_EQ(std::set<ConnectedComponent>(actual.begin(), actual.end()), expected);
}


INSTANTIATE_TEST_SUITE_P(
	Cases,
	TSTest,
	::testing::Values(
		std::make_tuple(
			std::initializer_list<DigraphEdge>{
                {1, 4}, {1, 6}, {2, 1}, {2, 7}, {3, 2},
                {3, 5}, {3, 8}, {4, 2}, {4, 6}, {4, 7},
                {5, 3}, {5, 8}, {6, 4}, {6, 9}, {8, 9},
                {8, 10}, {9, 7}, {10, 11}, {11, 8}, {12, 14},
                {12, 15}, {14, 15}
            },
            std::set<ConnectedComponent>{
                {1, 2, 4, 6},
                {3, 5},
                {7},
                {8, 10, 11},
                {9},
                {12},
                {14},
                {15}
            }
        )
	)
);
