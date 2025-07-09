#pragma once
#include <vector>
#include <memory>
#include <set>

class GeometricGraph {
public:
	struct Vertex;
	GeometricGraph();
	explicit GeometricGraph(const std::vector<Vertex>& vertices);
	GeometricGraph(const GeometricGraph& other);
    ~GeometricGraph();
    void AddVertex(int x, int y, const std::set<int>& neighbors);
	void AddVertex(const Vertex& vertex);
	Vertex& GetVertex(std::size_t index);
	Vertex operator[](std::size_t index);
	[[nodiscard]] std::set<int> ArticulationPoints() const;
	void Validate();
private:
    std::vector<Vertex> vertices;
};

struct GeometricGraph::Vertex {
	int x, y;
	std::set<int> neighbors;
};
