#include <gtest/gtest.h>
#include "Digraph.h"


class TSTest : public ::testing::TestWithParam<std::tuple<std::initializer_list<DigraphEdge>, int, int>> {};

TEST_P(TSTest, Tests) {
	auto [edges, countOfEdges, countOfNodes] = GetParam();
    Digraph graph(edges);
    auto actual = graph.Condensation();
    EXPECT_EQ(actual.getEdges().size(), countOfEdges) << "EXPECTED: " << countOfNodes << " ACTUAL: " << actual.getEdges().size();
    EXPECT_EQ(actual.getNodes().size(), countOfNodes) << "EXPECTED: " << countOfNodes << " ACTUAL: " << actual.getNodes().size();
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
            9,
            8
        ),
        std::make_tuple(
			std::initializer_list<DigraphEdge>{
                {1, 2}, {2, 3}, {3, 1}
            },
            0,
            1
        ),
        std::make_tuple(
			std::initializer_list<DigraphEdge>{
                {1, 2},
            },
            1,
            2
        ),
        std::make_tuple(
			std::initializer_list<DigraphEdge>{
                {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8},
            },
            7, 
            8
        ),
        std::make_tuple(
			std::initializer_list<DigraphEdge>{
                {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, 
                {2, 1}, {4, 3}, {6, 5}, {8, 7},
            },
            3, 
            4
        ),
        std::make_tuple(
			std::initializer_list<DigraphEdge>{
                {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, 
                {2, 1}, {3, 2}, {4, 3}, {5, 4}, {6, 5}, {7, 6}, {8, 7},
            },
            0,
            1
        ),
        std::make_tuple(
			std::initializer_list<DigraphEdge>{
                {1, 2}, {2, 3}, {3, 1},
                {4, 5}, {5, 6}, {6, 4},
            },
            0,
            2
        )
	)
);
