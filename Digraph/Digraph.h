#include <set>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using IdType = int;
using TimeType = int;
using ConnectedComponent = std::set<IdType>;
struct TimeMark {
	IdType id;
	TimeType entry;
	TimeType exit;
};

std::ostream& operator<<(std::ostream& os, const TimeMark& mark);

struct DigraphEdge {
	IdType u = -1;
	IdType v = -1;
};
std::ostream& operator<<(std::ostream& os, const DigraphEdge& edge);


struct DigraphNode {
	IdType id;
	std::set<IdType> neighbors;
};


class Digraph {
public:
	Digraph();
	Digraph(const std::initializer_list<DigraphEdge>& edges);
	Digraph(const std::vector<DigraphEdge>& edges);
	void addEdge(IdType u, IdType v);
	void addEdge(const DigraphEdge& edge);
	void operator+=(const DigraphEdge& edge);
	bool isConnected(IdType u, IdType v) const;
	bool operator()(IdType u, IdType v) const;
	std::set<IdType> getNeighbors(IdType u) const;
	std::set<IdType> operator[](IdType u) const;

	std::size_t size() const;
	void clear();
	std::vector<DigraphEdge> getEdges() const;
	std::vector<IdType> getNodes() const;

	std::vector<TimeMark> DFS() const;
	std::vector<TimeMark> DFS(const std::vector<IdType>& order) const;
	std::vector<TimeMark> DFSFragment(IdType start, const std::unordered_set<IdType>& visited, TimeType& currentTime) const;
	Digraph getTranspose() const;
	std::vector<ConnectedComponent> getConnectedComponents() const;
	static Digraph Condensation(const Digraph& graph, const std::vector<ConnectedComponent>& components);
	static Digraph Condensation(const Digraph& graph);
	Digraph Condensation() const;
private:
	std::unordered_map<IdType, DigraphNode> nodes;
};
