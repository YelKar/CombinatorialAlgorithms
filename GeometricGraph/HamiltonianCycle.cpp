#include "GeometricGraph.h"
#include <ranges>
#include <numeric>
#include "print.h"
#include "matrix.h"


std::vector<double> FindMinRowsElements(const GeometricGraph::AdjacencyMatrix& adjacencyMatrix) {
	auto container = std::ranges::subrange(adjacencyMatrix.begin() + 1, adjacencyMatrix.end()) | std::views::transform([] (const GeometricGraph::AdjacencyMatrixRow row) {
		return std::ranges::min(std::ranges::subrange(row.begin() + 1, row.end()));
	});
	return std::vector(std::begin(container), std::end(container));
}

std::vector<double> FindMinColumnsElements(const GeometricGraph::AdjacencyMatrix& adjacencyMatrix) {
	std::vector<double> container(adjacencyMatrix.size() - 1, GeometricGraph::INF);
	for (int i = 1; i < adjacencyMatrix.size(); ++i) {
		for (int j = 1; j < adjacencyMatrix.size(); ++j) {
			container[j - 1] = std::min(container[j - 1], adjacencyMatrix[i][j]);
		}
	}
	return container;
}

template <typename Container>
auto Sum(const Container& arr) {
	using ValueType = std::decay_t<decltype(*std::begin(arr))>;
	return std::accumulate(std::begin(arr), std::end(arr), ValueType{});
}

GeometricGraph::AdjacencyMatrix GetPenaltyMatrix(
	const GeometricGraph::AdjacencyMatrix& adjacencyMatrix,
	const auto& minRowsElements,
	const auto& minColumnsElements
) {
	GeometricGraph::AdjacencyMatrix penaltyMatrix(
		adjacencyMatrix.size(),
		GeometricGraph::AdjacencyMatrixRow(
			adjacencyMatrix.size(),
			GeometricGraph::INF
		)
	);
	for (int i = 1; i < adjacencyMatrix.size(); ++i) {
		penaltyMatrix[i][0] = i - 1;
		penaltyMatrix[0][i] = i - 1;
	}
	for (int i = 1; i < adjacencyMatrix.size(); ++i) {
		for (int j = 1; j < adjacencyMatrix.size(); ++j) {
			if (adjacencyMatrix[i][j] == 0) {
				penaltyMatrix[i][j] = minRowsElements[i - 1] + minColumnsElements[j - 1];
			}
		}
	}
	return penaltyMatrix;
}

struct Penalty {
	double value;
	int i, j;
	auto operator<=>(const Penalty& p) const {
		return value <=> p.value;
	}
};

Penalty MaxOfMatrix(const GeometricGraph::AdjacencyMatrix& matrix) {
	Penalty result{matrix[1][1], 0, 0};
	for (int i = 1; i < matrix.size(); i++) {
		for (int j = 1; j < matrix.size(); j++) {
			if (matrix[i][j] > result.value && matrix[i][j] != GeometricGraph::INF || result.value == GeometricGraph::INF) {
				result = {
					matrix[i][j],
					i - 1, j - 1,
				};
			}
		}
	}
	return result;
}

GeometricGraph::AdjacencyMatrix MatrixReduction(int i, int j, const GeometricGraph::AdjacencyMatrix& adjacencyMtx) {
	// std::cout << "MatrixReduction(" << i << ", " << j << ") => " << adjacencyMtx[i + 1][j + 1] << std::endl;
	// tools::PrintMatrix(adjacencyMtx);

	GeometricGraph::AdjacencyMatrix minor = adjacencyMtx;
	auto removeI = minor[i + 1][0];
	auto removeJ = minor[0][j + 1];

	for (int i = 1; i < minor.size(); i++) {
		for (int j = 1; j < minor[i].size(); j++) {
			if (removeI == minor[0][j] && removeJ == minor[i][0]) {
				minor[i][j] = GeometricGraph::INF;
			}
		}
	}

    minor.erase(minor.begin() + i + 1);
	for (auto& row : minor) {
		row.erase(row.begin() + j + 1);
	}
    
	// std::cout << "Matrix Reduction Result:" << std::endl;
	// tools::PrintMatrix(minor);
    
    return minor;
}

std::vector<GeometricGraph::Edge> GetOriginalCoordinates(
    int n,
    const std::vector<GeometricGraph::Edge>& steps
);

void FindHamiltonianCycle(
	GeometricGraph::AdjacencyMatrix adjacencyMatrixWithAxis,
	const std::vector<GeometricGraph::Edge>& path,
	std::vector<GeometricGraph::Edge>& bestPath,
	double& record,
	double bottomLimit = 0
)
{
	// std::cout << "------------------------>" << std::endl;
	// std::cout << "GOT:" << std::endl;
	// tools::PrintMatrix(adjacencyMatrixWithAxis);
	// std::cout << "BottomLimit: " << bottomLimit << " Record: " << record << std::endl;
	// std::cout << "Path: ";
	// tools::PrintArray(path);
	// std::cout << "\\/\\/\\/\\/\\/\\/" << std::endl;
	if (adjacencyMatrixWithAxis.size() < 3) {
		if (bottomLimit < record && adjacencyMatrixWithAxis.size() == 2 && adjacencyMatrixWithAxis[1][1] != GeometricGraph::INF) {
			record = bottomLimit;
			bestPath = path;
			bestPath.push_back({adjacencyMatrixWithAxis[1][0], adjacencyMatrixWithAxis[0][1]});
			record += adjacencyMatrixWithAxis[1][1];
			// std::cout << "New record: " << record << std::endl;
			// std::cout << "New path: " << std::endl;
			// tools::PrintArray(bestPath);
		}
		return;
	}
	auto minRowsElements = FindMinRowsElements(adjacencyMatrixWithAxis);
	for (int i = 1; i < adjacencyMatrixWithAxis.size(); ++i) {
		for (int j = 1; j < adjacencyMatrixWithAxis[i].size(); ++j) {
			if (adjacencyMatrixWithAxis[i][j] != GeometricGraph::INF) {
				adjacencyMatrixWithAxis[i][j] -= minRowsElements[i - 1];
			}
		}
	}
	// std::cout << "RowSubtracted:" << std::endl;
	// tools::PrintMatrix(adjacencyMatrixWithAxis);
	// std::cout << "MinRowsElements:" << std::endl;
	// tools::PrintArray(minRowsElements);
	auto minColumnsElements = FindMinColumnsElements(adjacencyMatrixWithAxis);
	for (int i = 1; i < adjacencyMatrixWithAxis.size(); ++i) {
		for (int j = 1; j < adjacencyMatrixWithAxis[i].size(); ++j) {
			if (adjacencyMatrixWithAxis[i][j] != GeometricGraph::INF) {
				adjacencyMatrixWithAxis[i][j] -= minColumnsElements[j - 1];
			}
		}
	}

	// std::cout << "ColSubtracted:" << std::endl;
	// tools::PrintMatrix(adjacencyMatrixWithAxis);
	// std::cout << "MinColumnsElements:" << std::endl;
	// tools::PrintArray(minColumnsElements);

	if (
		std::all_of(minColumnsElements.begin(), minColumnsElements.end(), [] (auto val) {
			return val == GeometricGraph::INF;
		})
		|| std::all_of(minRowsElements.begin(), minRowsElements.end(), [] (auto val) {
			return val == GeometricGraph::INF;
		})
	) {
		return;
	}

	bottomLimit +=
		+ Sum(minRowsElements)
		+ Sum(minColumnsElements);
	// std::cout << "BottomLimit: " << bottomLimit << std::endl;
	
	if (bottomLimit > record) {
		return;
	}

	auto penaltyMatrix = GetPenaltyMatrix(adjacencyMatrixWithAxis, minRowsElements, minColumnsElements);
	auto maxPenalty = MaxOfMatrix(penaltyMatrix);
	// std::cout << "PenaltyMatrix:" << std::endl;
	// tools::PrintMatrix(penaltyMatrix);
	// std::cout 
	// 	<< "value: " << maxPenalty.value 
	// 	<< "| i: " << maxPenalty.i
	// 	<< "| j: " << maxPenalty.j << std::endl;
	
	auto newMtx = MatrixReduction(maxPenalty.i, maxPenalty.j, adjacencyMatrixWithAxis);
	// std::cout << "FirstBranchMatrix:" << std::endl;
	// tools::PrintMatrix(newMtx);
	auto newPath = path;
	newPath.emplace_back(adjacencyMatrixWithAxis[maxPenalty.i + 1][0], adjacencyMatrixWithAxis[0][maxPenalty.j + 1]);
	// std::cout << "NewEdge:" << GeometricGraph::Edge(adjacencyMatrixWithAxis[maxPenalty.i + 1][0], adjacencyMatrixWithAxis[0][maxPenalty.j + 1]) << " Penalty: " << maxPenalty.value << std::endl;
	// std::cout << "<------------------------>" << std::endl;
	FindHamiltonianCycle(newMtx, newPath, bestPath, record, bottomLimit);

	newMtx = adjacencyMatrixWithAxis;
	newMtx[maxPenalty.i + 1][maxPenalty.j + 1] = GeometricGraph::INF;
	// std::cout << "SecondBranchMatrix:" << std::endl;
	// tools::PrintMatrix(newMtx);
	// std::cout << "<-------------------------" << std::endl;
	FindHamiltonianCycle(newMtx, path, bestPath, record, bottomLimit);
}

void SortChainedPairs(std::vector<std::pair<int, int>>& arr) {
    for (size_t i = 0; i + 1 < arr.size(); ++i) {
        if (arr[i].second != arr[i + 1].first) {
            for (size_t j = i + 2; j < arr.size(); ++j) {
                if (arr[i].second == arr[j].first) {
                    std::rotate(arr.begin() + i + 1, arr.begin() + j, arr.begin() + j + 1);
                    break;
                }
            }
        }
    }
}

std::vector<GeometricGraph::Edge> GetOriginalCoordinates(
    int n,
    const std::vector<GeometricGraph::Edge>& steps
) {
    std::vector<int> row_map(n), col_map(n);
    std::iota(row_map.begin(), row_map.end(), 0);
    std::iota(col_map.begin(), col_map.end(), 0);

    std::vector<std::pair<int, int>> result;
    for (const auto& step : steps) {
        int i = step.first;
        int j = step.second;

        if (i >= static_cast<int>(row_map.size()) || j >= static_cast<int>(col_map.size())) {
            throw std::out_of_range("Index out of current matrix bounds");
        }

        result.emplace_back(row_map[i], col_map[j]);

        row_map.erase(row_map.begin() + i);
        col_map.erase(col_map.begin() + j);
    }

	SortChainedPairs(result);

    return result;
}