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
	const double Inf = GeometricGraph::INF;
	// GeometricGraph::AdjacencyMatrix mtx{
	// 			{inf, 1, 2},
	// 			{1, inf, 3},
	// 			{2, 3, inf}
	// };
	// GeometricGraph::AdjacencyMatrix mtx{
	// 			{inf, 8, 1, inf, 3, inf},
	// 			{8, inf, 6, 5, inf, inf},
	// 			{1, 6, inf, 4, 5, inf},
	// 			{inf, 5, 4, inf, 6, 4},
	// 			{3, inf, 5, 6, inf, 7},
	// 			{inf, inf, inf, 4, 7, inf},
	// };
	GeometricGraph::AdjacencyMatrix mtx{
				{ Inf, 8, Inf, Inf, Inf, Inf, Inf, 4, Inf },
				{ 8, Inf, 2, Inf, Inf, Inf, Inf, Inf, Inf },
				{ Inf, 2, Inf, 1, Inf, Inf, Inf, Inf, 1 },
				{ Inf, Inf, 1, Inf, 2, Inf, Inf, Inf, Inf },
				{ Inf, Inf, Inf, 2, Inf, 1, 1, Inf, Inf },
				{ Inf, Inf, Inf, Inf, 1, Inf, 100, Inf, Inf },
				{ Inf, Inf, Inf, Inf, 1, 100, Inf, 1, 1 },
				{ 4, Inf, Inf, Inf, Inf, Inf, 1, Inf, 1 },
				{ Inf, Inf, 1, Inf, Inf, Inf, 1, 1, Inf },
			};
	tools::PrintMatrix(mtx);
	auto path = GeometricGraph::HamiltonianCycle(mtx);
	tools::PrintArray(path);
	std::cout << GeometricGraph::GetLength(mtx, path) << std::endl;
	return 0;
}