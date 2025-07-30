#include "GeometricGraph.h"
#include <ranges>
#include <numeric>
#include "print.h"
#include "matrix.h"


std::vector<double> FindMinRowsElements(const GeometricGraph::AdjacencyMatrix& adjacencyMatrix) {
	auto container = adjacencyMatrix | std::views::transform([] (const GeometricGraph::AdjacencyMatrixRow row) {
		return std::ranges::min(row);
	});
	return std::vector(std::begin(container), std::end(container));
}

std::vector<double> FindMinColumnsElements(const GeometricGraph::AdjacencyMatrix& adjacencyMatrix) {
	auto container = std::views::iota(0ul, adjacencyMatrix.size()) | std::views::transform([adjacencyMatrix] (int columnNum) {
		return std::ranges::min(
			adjacencyMatrix
			| std::views::transform([columnNum] (const GeometricGraph::AdjacencyMatrixRow& row) {
				return row[columnNum];
			})
		);
	});
	return std::vector(std::begin(container), std::end(container));
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
			std::numeric_limits<double>::max()
		)
	);
	for (int i = 0; i < adjacencyMatrix.size(); ++i) {
		for (int j = 0; j < adjacencyMatrix.size(); ++j) {
			if (adjacencyMatrix[i][j] == 0) {
				penaltyMatrix[i][j] = minRowsElements[i] + minColumnsElements[j];
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
	Penalty result{matrix[0][0], 0, 0};
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			if (matrix[i][j] > result.value && matrix[i][j] != std::numeric_limits<double>::max() || result.value == std::numeric_limits<double>::max()) {
				result = {
					matrix[i][j],
					i, j,
				};
			}
		}
	}
	return result;
}

GeometricGraph::AdjacencyMatrix MatrixReduction(int i, int j, const GeometricGraph::AdjacencyMatrix& adjacencyMtx) {
	GeometricGraph::AdjacencyMatrix minor;
    minor.reserve(adjacencyMtx.size() - 1);
    
    for (int row = 0; row < adjacencyMtx.size(); ++row) {
        if (row == i) continue;
        
        const auto& originalRow = adjacencyMtx[row];
        auto& newRow = minor.emplace_back();
        newRow.reserve(originalRow.size() - 1);
        
        for (int col = 0; col < originalRow.size(); ++col) {
            if (col == j) continue;
			if (col == i && row == j) {
				newRow.push_back(std::numeric_limits<double>::max());
			} else {
            	newRow.push_back(originalRow[col]);
			}
        }
    }
    
    return minor;
}
int a = 0;

void FindHamiltonianCycle(
	GeometricGraph::AdjacencyMatrix adjacencyMatrix,
	const std::vector<GeometricGraph::Edge>& path,
	std::vector<GeometricGraph::Edge>& bestPath,
	double& record,
	double bottomLimit = 0
)
{
	std::cout << "------------------------>" << std::endl;
	std::cout << "GOT:" << std::endl;
	tools::PrintMatrix(adjacencyMatrix);
	if (++a >= 200) {
		return;
	}
	std::cout << "BottomLimit: " << bottomLimit << std::endl;
	std::cout << "\\/\\/\\/\\/\\/\\/" << std::endl;
	if (adjacencyMatrix.size() < 2) {
		if (!adjacencyMatrix.empty() && !adjacencyMatrix[0].empty() && bottomLimit < record) {
			record = bottomLimit;
			bestPath = path;
			std::cout << "New record: " << record << std::endl;
			std::cout << "New path: " << std::endl;
			tools::PrintArray(bestPath);
		}
		return;
	}
	auto minRowsElements = FindMinRowsElements(adjacencyMatrix);
	for (auto [row, minElement] : std::views::zip(adjacencyMatrix, minRowsElements)) {
		for (auto &element : row) {
			if (element != std::numeric_limits<double>::max())
				element -= minElement;
		}
	}
	std::cout << "RowSubtracted:" << std::endl;
	tools::PrintMatrix(adjacencyMatrix);
	std::cout << "MinRowsElements:" << std::endl;
	tools::PrintArray(minRowsElements);
	auto minColumnsElements = FindMinColumnsElements(adjacencyMatrix);
	for (auto [columnNum, minElement] : std::views::zip(std::views::iota(0ul, adjacencyMatrix.size()), minColumnsElements)) {
		for (auto &row : adjacencyMatrix) {
			if (row[columnNum] != std::numeric_limits<double>::max())
				row[columnNum] -= minElement;
		}
	}

	std::cout << "ColSubtracted:" << std::endl;
	tools::PrintMatrix(adjacencyMatrix);
	std::cout << "MinColumnsElements:" << std::endl;
	tools::PrintArray(minColumnsElements);

	bottomLimit +=
		+ Sum(minRowsElements)
		+ Sum(minColumnsElements);
	std::cout << "BottomLimit: " << bottomLimit << std::endl;
	
	if (bottomLimit > record) {
		return;
	}

	auto penaltyMatrix = GetPenaltyMatrix(adjacencyMatrix, minRowsElements, minColumnsElements);
	auto maxPenalty = MaxOfMatrix(penaltyMatrix);
	std::cout << "PenaltyMatrix:" << std::endl;
	tools::PrintMatrix(penaltyMatrix);
	std::cout 
		<< "value: " << maxPenalty.value 
		<< "| i: " << maxPenalty.i 
		<< "| j: " << maxPenalty.j << std::endl;
	
	auto newMtx = MatrixReduction(maxPenalty.i, maxPenalty.j, adjacencyMatrix);
	std::cout << "FirstBranchMatrix:" << std::endl;
	tools::PrintMatrix(newMtx);
	auto newPath = path;
	newPath.emplace_back(maxPenalty.i, maxPenalty.j);
	std::cout << "NewEdge:" << GeometricGraph::Edge(maxPenalty.i, maxPenalty.j) << " Penalty: " << maxPenalty.value << std::endl;
	std::cout << "<------------------------>" << std::endl;
	FindHamiltonianCycle(newMtx, newPath, bestPath, record, bottomLimit);

	newMtx = adjacencyMatrix;
	newMtx[maxPenalty.i][maxPenalty.j] = std::numeric_limits<double>::max();
	std::cout << "SecondBranchMatrix:" << std::endl;
	tools::PrintMatrix(newMtx);
	std::cout << "<-------------------------" << std::endl;
	FindHamiltonianCycle(newMtx, path, bestPath, record, bottomLimit);
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

    return result;
}