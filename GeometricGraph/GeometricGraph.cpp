#include <stdexcept>
#include "GeometricGraph.h"
#include "limits"
#include <stack>
#include <iostream>
#include <cmath>
#include <numeric>
#include <ranges>


GeometricGraph::GeometricGraph() = default;
GeometricGraph::GeometricGraph(const std::vector<Vertex>& vertices) : vertices(vertices) {}
GeometricGraph::GeometricGraph(const GeometricGraph& other) : vertices(other.vertices) {}
GeometricGraph::~GeometricGraph() = default;

void GeometricGraph::AddVertex(int x, int y, const std::set<int>& neighbors)
{
	AddVertex({x, y, neighbors});
}

void GeometricGraph::AddVertex(const Vertex& vertex)
{
	vertices.push_back(vertex);
}

GeometricGraph::Vertex& GeometricGraph::GetVertex(std::size_t index)
{
	if (index >= vertices.size()) {
		throw std::out_of_range("GeometricGraph::GetVertex");
	}
	return vertices[index];
}

const GeometricGraph::Vertex &GeometricGraph::GetVertex(std::size_t index) const
{
	if (index >= vertices.size()) {
		throw std::out_of_range("GeometricGraph::GetVertex");
	}
	return vertices[index];
}

GeometricGraph::Vertex GeometricGraph::operator[](std::size_t index)
{
	return GetVertex(index);
}

struct SearchTreeVertex {
	int id{};
	std::vector<std::shared_ptr<SearchTreeVertex>> children;
};

std::set<int> ProcessSearchTree(const std::shared_ptr<SearchTreeVertex>& root, std::vector<int> in, std::vector<int> up)
{
	std::stack<std::shared_ptr<SearchTreeVertex>> treeState;
	std::set<int> result;

	if (root->children.size() >= 2) {
		result.insert(0);
	}

	treeState.push(root);

	for (;!treeState.empty();) {
		auto node = treeState.top();
		treeState.pop();

		for (const auto& child : node->children) {
			if (node->id != 0 && up[child->id] >= in[node->id]) {
				result.insert(node->id);
			}
			treeState.push(child);
		}
	}

	return result;
}

std::shared_ptr<SearchTreeVertex> TreeTraversal(
	const std::vector<GeometricGraph::Vertex>& vertices,
	std::vector<int> in,
	std::vector<int> up
) {
	auto searchTreeRoot = std::make_shared<SearchTreeVertex>(0);
	std::stack<std::pair<int, bool>> state;
	for (int i = static_cast<int>(vertices.size()) - 1; i >= 0; i--) {
		state.emplace(i, false);
	}

	std::stack<std::shared_ptr<SearchTreeVertex>> treeState;
	treeState.push(searchTreeRoot);

	for (int time = 0; !state.empty(); ++time) {
		auto [vertex, isExit] = state.top();

		state.pop();
		if (isExit) {
			treeState.pop();
			continue;
		}
		if (in[vertex] != -1) {
			continue;
		}
		if (vertex != 0) {
			auto newNode = std::make_shared<SearchTreeVertex>(vertex);
			treeState.top()->children.push_back(newNode);
			treeState.push(newNode);
		}
		state.emplace(vertex, true);

		in[vertex] = up[vertex] = time;

		int minUp = up[vertex];
		int countOfVisitedNeighbours = 0;
		for (int neighbour : vertices[vertex].neighbors) {
			if (in[neighbour] != -1) {
				minUp = std::min(minUp, in[neighbour]);
				countOfVisitedNeighbours++;
			} else {
				state.emplace(neighbour, false);
			}
		}
		if (countOfVisitedNeighbours > 1) {
			up[vertex] = minUp;
		}
	}
	return searchTreeRoot;
}

std::set<int> GeometricGraph::ArticulationPoints() const
{
	std::vector<int>
	    in(vertices.size(), -1),
	    up(vertices.size(), std::numeric_limits<int>::max());

	auto root = TreeTraversal(vertices, in, up);

	return ProcessSearchTree(root, in, up);
}

void GeometricGraph::Validate() const
{
	for (int vertex = 0; vertex < vertices.size(); vertex++) {
		for (int neighbour : vertices[vertex].neighbors) {
			if (neighbour >= vertices.size()) {
				throw std::runtime_error("Vertex " + std::to_string(neighbour) + " out of range");
			}
		}
	}
}

bool GeometricGraph::HasEdge(int v1, int v2) const
{
	return GetVertex(v1).neighbors.contains(v2);
}

double GeometricGraph::GetLength(int v1, int v2) const
{
	auto
	    vertex1 = GetVertex(v1),
	    vertex2 = GetVertex(v2);
	if (HasEdge(v1, v2)) {
		return std::hypot(vertex1.x - vertex2.x, vertex1.y - vertex2.y);
	}
	throw std::invalid_argument(std::format("Vertices {} and {} are not neighbors", v1, v2));
}

double GeometricGraph::GetLength(const GeometricGraph::AdjacencyMatrix& mtx, const std::vector<Edge>& path)
{
	double length = 0;
	for (const auto& edge : path) {
		if (edge.first >= mtx.size() || edge.second >= mtx[edge.first].size()) {
			throw std::invalid_argument("Edge [" + std::to_string(edge.first) + ";" + std::to_string(edge.second) + "] out of range");
		}
		length += mtx[edge.first][edge.second];
	}
	return length;
}

GeometricGraph::AdjacencyMatrix GeometricGraph::GetAdjacencyMatrix() const
{
	std::vector<std::vector<double>> matrix(vertices.size());
	for (int row = 0; row < vertices.size(); ++row) {
		matrix[row].resize(vertices.size(), GeometricGraph::INF);
		for (int vertex = 0; vertex < vertices.size(); ++vertex) {
			if (HasEdge(row, vertex)) {
				matrix[row][vertex] = GetLength(row, vertex);
			}
		}
	}
	return matrix;
}

#include "HamiltonianCycle.cpp"

std::vector<GeometricGraph::Edge> GeometricGraph::HamiltonianCycle() const
{
	return HamiltonianCycle(GetAdjacencyMatrix());;
}

std::vector<GeometricGraph::Edge> GeometricGraph::HamiltonianCycle(const GeometricGraph::AdjacencyMatrix& adjacencyMatrix)
{
	double record = GeometricGraph::INF;
	std::vector<Edge> path;
	std::vector<Edge> bestPath;
	GeometricGraph::AdjacencyMatrix adjacencyMatrixWithAxis = adjacencyMatrix;
	adjacencyMatrixWithAxis.insert(adjacencyMatrixWithAxis.begin(), std::vector<double>(adjacencyMatrixWithAxis.size() + 1, -1));
	for (int i = 1; i < adjacencyMatrixWithAxis.size(); i++) {
		adjacencyMatrixWithAxis[i].insert(adjacencyMatrixWithAxis[i].begin(), i - 1);
		adjacencyMatrixWithAxis[0][i] = i - 1;
	}
	FindHamiltonianCycle(adjacencyMatrixWithAxis, path, bestPath, record);
	// tools::PrintArray(bestPath);
	// std::cout << "Record: " << record << " Length: " << GeometricGraph::GetLength(adjacencyMatrix, bestPath) << std::endl;
	return bestPath;
}


std::ostream& operator<<(std::ostream& os, const GeometricGraph::Edge& edge) {
	return os << "[" << edge.first << ";" << edge.second << "]";
}
