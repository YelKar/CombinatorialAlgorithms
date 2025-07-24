#pragma once
#include <vector>
#include <memory>
#include <set>

class GeometricGraph {
public:
	struct Vertex;
	using AdjacencyMatrixRow = std::vector<double>;
	using AdjacencyMatrix = std::vector<AdjacencyMatrixRow>;
	GeometricGraph();
	explicit GeometricGraph(const std::vector<Vertex>& vertices);
	GeometricGraph(const GeometricGraph& other);
    ~GeometricGraph();
    void AddVertex(int x, int y, const std::set<int>& neighbors);
	void AddVertex(const Vertex& vertex);
	Vertex& GetVertex(std::size_t index);
	[[nodiscard]] const Vertex& GetVertex(std::size_t index) const;
	Vertex operator[](std::size_t index);
	[[nodiscard]] std::set<int> ArticulationPoints() const;
	void Validate() const;
	[[nodiscard]] bool HasEdge(int v1, int v2) const;
	[[nodiscard]] double GetLength(int v1, int v2) const;
	[[nodiscard]] std::vector<std::vector<double>> GetAdjacencyMatrix() const;
	[[nodiscard]] std::vector<int> HamiltonianCycle(int startAt = 0) const;
private:
    std::vector<Vertex> vertices;
};

struct GeometricGraph::Vertex {
	int x, y;
	std::set<int> neighbors;
};
