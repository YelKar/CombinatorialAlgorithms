#include "GeometricGraph.h"
#include "print.h"
#include "matrix.h"
#include <iomanip>

int main(int argc, char **argv) {
	// GeometricGraph graph;
	// graph.AddVertex(85, 10, {1, 2, 4});
	// graph.AddVertex(15, 0, {0, 2, 3});
	// graph.AddVertex(55, 30, {0, 1, 3, 4});
	// graph.AddVertex(0, 45, {1, 2, 4, 5});
	// graph.AddVertex(90, 55, {0, 2, 3, 5});
	// graph.AddVertex(30, 85, {3, 4});

	// graph.Validate();

	// auto mtx = graph.GetAdjacencyMatrix();
	// for (const auto& row : mtx) {
	// 	tools::PrintArray(row, "\t");
	// }
	// tools::PrintArray(graph.HamiltonianCycle());
	const double inf = std::numeric_limits<double>::max();
	GeometricGraph::AdjacencyMatrix mtx{
				{inf, 1, 2},
				{1, inf, 3},
				{2, 3, inf}
	};
	tools::PrintMatrix(mtx);
	auto path = GeometricGraph::HamiltonianCycle(mtx);
	tools::PrintArray(path);
	return 0;
}