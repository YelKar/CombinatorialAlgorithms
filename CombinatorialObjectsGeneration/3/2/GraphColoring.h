#include <vector>
#include <set>
#include <map>
#include "PermutationWithRepetition.h"


using Vertex = int;
using Edge = std::pair<Vertex, Vertex>;
using Face = std::vector<Edge>;
using Graph = std::vector<Face>;

using DualGraph = std::vector<std::set<int>>;

Edge NormalizeEdge(Edge e) {
	return (e.first < e.second) ? e : Edge{e.second, e.first};
}

DualGraph BuildDualGraph(const Graph& faces) {
	std::map<Edge, std::vector<int>> edgeToFaces;

	for (int faceNumber = 0; faceNumber < faces.size(); ++faceNumber) {
		for (Edge e : faces[faceNumber]) {
			edgeToFaces[NormalizeEdge(e)].push_back(faceNumber);
		}
	}

	DualGraph dual;
	dual.resize(faces.size());

	for (const auto& [edge, faceList] : edgeToFaces) {
		if (faceList.size() == 2) {
			int f1 = faceList[0];
			int f2 = faceList[1];
			dual[f1].insert(f2);
			dual[f2].insert(f1);
		}
	}

	return dual;
}

bool IsValidColoring(const std::vector<std::set<int>>& graph, const std::vector<int>& coloring) {
	const int n = graph.size();
	for (int u = 0; u < n; ++u) {
		for (int v : graph[u]) {
			if (v < u && coloring[u] == coloring[v]) {
				return false;
			}
		}
	}
	return true;
}

bool GraphColoring(const std::vector<std::set<int>>& graph, std::vector<int>& result) {
	const int n = graph.size();

	for (int colors = 1; colors <= n; ++colors) {
		std::vector<int> coloring(n, 0);
		do {
			if (IsValidColoring(graph, coloring)) {
				result = coloring;
				return true;
			}
		} while (PermutationWithRepetition::Next(coloring, colors));
	}
	return false;
}

