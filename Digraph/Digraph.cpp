#include "Digraph.h"
#include <ranges>
#include <algorithm>
#include <stack>

Digraph::Digraph() = default;

Digraph::Digraph(const std::vector<DigraphEdge>& edges) {
    for (const auto& edge : edges) {
        addEdge(edge.u, edge.v);
    }
}

Digraph::Digraph(const std::initializer_list<DigraphEdge>& edges)
	: Digraph(std::vector<DigraphEdge>(edges)) {}

void Digraph::addEdge(IdType u, IdType v) {
    auto it = nodes.find(u);
    if (it == nodes.end()) {
        nodes[u].id = u;
		nodes[u].neighbors = {};
    }
    nodes[u].neighbors.insert(v);
	it = nodes.find(v);
	if (it == nodes.end()) {
		nodes[v].id = v;
		nodes[v].neighbors = {};
	}
}

void Digraph::addEdge(const DigraphEdge& edge) {
    addEdge(edge.u, edge.v);
}

void Digraph::addNode(IdType nodeId) {
    auto it = nodes.find(nodeId);
	if (it == nodes.end()) {
		nodes[nodeId].id = nodeId;
		nodes[nodeId].neighbors = {};
	}
}

void Digraph::operator+=(const DigraphEdge& edge) {
    addEdge(edge.u, edge.v);
}

bool Digraph::isConnected(IdType u, IdType v) const {
    auto it = nodes.find(u);
    if (it == nodes.end()) return false;
    return it->second.neighbors.find(v) != it->second.neighbors.end();
}

bool Digraph::operator()(IdType u, IdType v) const {
	return isConnected(u, v);
}

std::set<IdType> Digraph::getNeighbors(IdType u) const {
    auto it = nodes.find(u);
    if (it == nodes.end()) return {};
    return it->second.neighbors;
}

std::set<IdType> Digraph::operator[](IdType u) const {
    return getNeighbors(u);
}

std::size_t Digraph::size() const {
	return nodes.size();
}

void Digraph::clear() {
	nodes.clear();
}

std::vector<DigraphEdge> Digraph::getEdges() const {
	std::vector<DigraphEdge> edges;
	for (const auto& [id, node] : nodes) {
		for (IdType v : node.neighbors) {
			edges.push_back({id, v});
		}
	}
	return edges;
}

std::vector<IdType> Digraph::getNodes() const {
	std::vector<IdType> keys;
	for (const auto& [id, node] : nodes) {
		keys.push_back(id);
	}
	return keys;
}

std::vector<TimeMark> Digraph::DFSFragment(IdType start, const std::unordered_set<IdType>& visited, TimeType& currentTime) const {
    std::unordered_set<IdType> visitedSet(visited);
    std::vector<TimeMark> result;
    std::stack<std::pair<IdType, bool>> stack;
    stack.push({ start, false });

    std::unordered_map<IdType, size_t> idToIndex; // Чтобы быстро находить TimeMark по id

    while (!stack.empty()) {
        IdType current = stack.top().first;
        bool isVisited = stack.top().second;
        stack.pop();

        if (isVisited) {
            result[idToIndex[current]].exit = currentTime++;
            continue;
        }

        if (visitedSet.count(current)) continue;
        visitedSet.insert(current);

        idToIndex[current] = result.size(); // Сохраняем индекс
        result.push_back({ current, currentTime++, -1 });

        stack.push({ current, true });

        const auto& neighbors = getNeighbors(current);
        for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
            if (!visitedSet.count(*it)) {
                stack.push({ *it, false });
            }
        }
    }

    return result;
}

std::vector<TimeMark> Digraph::DFS() const {
    return DFS(getNodes());
}

std::vector<TimeMark> Digraph::DFS(const std::vector<IdType>& order) const {
    std::unordered_set<IdType> visited;
    std::vector<TimeMark> traversal;
    TimeType currentTime = 0;

    for (IdType id : order) {
        if (!visited.count(id)) {
            auto fragment = DFSFragment(id, visited, currentTime);
            for (const auto& mark : fragment) {
                visited.insert(mark.id);
                traversal.push_back(mark);
            }
        }
    }

    return traversal;
}

Digraph Digraph::getTranspose() const {
    Digraph transpose;
    for (const auto& edge : getEdges()) {
        transpose.addEdge(edge.v, edge.u);
    }
    return transpose;
}

std::vector<ConnectedComponent> Digraph::getConnectedComponents() const {
    auto dfs = DFS();
    std::ranges::sort(dfs, [](const TimeMark& a, const TimeMark& b) {
        return a.exit >= b.exit;
    });
    
    auto transpose = getTranspose();
    std::vector<ConnectedComponent> components;
    std::unordered_set<IdType> visited;
    for (const auto& mark : dfs) {
        if (!visited.count(mark.id)) {
            TimeType _ = 0;
            auto componentTimeMarks = transpose.DFSFragment(mark.id, visited, _);
            ConnectedComponent component;
            for (const auto& timeMark : componentTimeMarks) {
                component.insert(timeMark.id);
                visited.insert(timeMark.id);
            }
            components.push_back(component);
        }
    }
    return components;
}

Digraph Digraph::Condensation(const Digraph& graph, const std::vector<ConnectedComponent>& components) {
	std::unordered_map<IdType, int> nodeToComponent;
	for (int i = 0; i < static_cast<int>(components.size()); ++i) {
		for (IdType v : components[i]) {
			nodeToComponent[v] = i;
		}
	}

	Digraph result;

    for (const auto& [_, componentId] : nodeToComponent) {
        result.addNode(componentId);
    }

	for (int i = 0; i < static_cast<int>(components.size()); ++i) {
		for (IdType u : components[i]) {
			const auto& neighbors = graph[u];
			for (IdType v : neighbors) {
				auto it = nodeToComponent.find(v);
				if (it == nodeToComponent.end())
					continue;

				int compTo = it->second;
				if (compTo != i) {
					result.addEdge(i, compTo);
				}
			}
		}
	}

	return result;
}

Digraph Digraph::Condensation(const Digraph& graph) {
    return Condensation(graph, graph.getConnectedComponents());
}

Digraph Digraph::Condensation() const {
    return Condensation(*this);
}

bool Digraph::operator==(const Digraph& graph) const {
    return nodes.size() == graph.nodes.size() && std::all_of(nodes.begin(), nodes.end(), [graph] (auto nodePair) {
        const auto [key, node] = nodePair;
        return graph.getNeighbors(key) == node.neighbors;
    });
}

std::ostream& operator<<(std::ostream& os, const DigraphEdge& edge)  {
	return os << "[" << edge.u << " -> " << edge.v << "]";
}

std::ostream& operator<<(std::ostream& os, const TimeMark& mark) {
	return os << "[" << mark.id << ": " << mark.entry << " - " << mark.exit << "]";
}
