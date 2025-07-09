#include "GeometricGraph.h"
#include "print.h"

int main(int argc, char **argv) {
	GeometricGraph graph;
	graph.AddVertex(0, 0, {1, 6});
	graph.AddVertex(0, 0, {0, 10, 2});
	graph.AddVertex(0, 0, {1, 3, 4});
	graph.AddVertex(0, 0, {2, 4, 5});
	graph.AddVertex(0, 0, {2, 3});
	graph.AddVertex(0, 0, {3});
	graph.AddVertex(0, 0, {0, 7, 8});
	graph.AddVertex(0, 0, {6, 8});
	graph.AddVertex(0, 0, {6, 7, 9});
	graph.AddVertex(0, 0, {8});
	graph.AddVertex(0, 0, {1});
	graph.Validate();
	auto resultSet = graph.ArticulationPoints();
	std::vector<int> result(resultSet.begin(), resultSet.end());
	tools::PrintArray(result);
	return 0;
}