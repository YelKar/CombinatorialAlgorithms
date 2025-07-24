#include <gtest/gtest.h>
#include <cmath>
#include "GraphColoring.h"



class Tests : public ::testing::TestWithParam<Graph> {};

TEST_P(Tests, Check) {
	const auto& graph = GetParam();
	auto dual = BuildDualGraph(graph);
	std::vector<int> colors;
	EXPECT_TRUE(GraphColoring(dual, colors));
	EXPECT_LE(std::set<int>(colors.begin(), colors.end()).size(), 4);

	for (int i = 0; i < dual.size(); ++i) {
		for (int neighbor : dual[i]) {
			EXPECT_NE(colors[i], colors[neighbor]);
		}
	}
}

INSTANTIATE_TEST_SUITE_P(
	Cases,
	Tests,
	::testing::Values(  // capacity, expectedResultWeight, expectedResultValue, things
		Graph{  // Треугольник
			{{1, 2}, {2, 3}, {3, 1}},
			{{1, 2}, {2, 3}, {3, 1}},
		},
		Graph{  // Шестиугольник
			{{0, 2}, {2, 3}, {3, 5}, {5, 4}, {4, 1}, {1, 0}},
			{{0, 2}, {2, 3}, {3, 5}, {5, 4}, {4, 1}, {1, 0}},
		},
		Graph{  // Квадрат с диагональю
			{{0, 1}, {1, 2}, {2, 0}},
			{{2, 1}, {1, 3}, {3, 2}},
			{{0, 1}, {1, 3}, {3, 2}, {2, 0}},
		},
		Graph{
			{{0, 1}, {1, 2}, {2, 0}},
			{{1, 2}, {1, 3}, {2, 3}},
			{{1, 3}, {3, 4}, {4, 1}},
			{{5, 3}, {3, 4}, {4, 5}},
			{{2, 3}, {3, 5}, {5, 6}, {6, 2}},
			{{0, 2}, {2, 6}, {6, 5}, {5, 4}, {4, 1}, {1, 0}},
		},
		Graph{  // Куб
			{{1, 2}, {2, 3}, {3, 4}, {4, 1}},
			{{1, 2}, {2, 6}, {6, 5}, {5, 1}},
			{{2, 3}, {3, 7}, {7, 6}, {6, 2}},
			{{3, 4}, {4, 8}, {8, 7}, {7, 3}},
			{{4, 1}, {1, 5}, {5, 8}, {8, 4}},
			{{5, 6}, {6, 7}, {7, 8}, {8, 5}},
		},
		Graph{  // Пятиконечная звезда
			{{0, 1}, {1, 2}, {2, 0}},
			{{0, 2}, {2, 3}, {3, 0}},
			{{0, 3}, {3, 4}, {4, 0}},
			{{0, 4}, {4, 5}, {5, 0}},
			{{0, 5}, {5, 1}, {1, 0}},
			{{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 1}},
		}
	)
);

TEST(OtherTests, OneEdge) {
	Graph faces = {{{1, 2}}};
	DualGraph dual = BuildDualGraph(faces);
	std::vector<int> colors;
	EXPECT_TRUE(GraphColoring(dual, colors));
	EXPECT_EQ(colors.size(), 1);
	EXPECT_EQ(colors[0], 0);
}
