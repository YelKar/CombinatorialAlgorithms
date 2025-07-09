#include <stdexcept>
#include "GeometricGraph.h"
#include "limits"
#include <stack>
#include <iostream>


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
	for (int neighbour : vertex.neighbors) {
		if (vertices.size() > neighbour)
		{
			vertices[neighbour].neighbors.insert(vertices.size() - 1);
		}
	}
}

GeometricGraph::Vertex& GeometricGraph::GetVertex(std::size_t index)
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

void GeometricGraph::Validate()
{
	for (int vertex = 0; vertex < vertices.size(); vertex++) {
		for (int neighbour : vertices[vertex].neighbors) {
			if (neighbour < vertices.size()) {
				vertices[neighbour].neighbors.insert(vertex);
			} else {
				throw std::runtime_error("Vertex " + std::to_string(neighbour) + " out of range");
			}
		}
	}
}
