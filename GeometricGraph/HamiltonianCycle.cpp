#include "GeometricGraph.h"
#include <ranges>
#include <numeric>
#include "print.h"
#include "matrix.h"


auto FindMinRowsElements(const GeometricGraph::AdjacencyMatrix& adjacencyMatrix) {
	return adjacencyMatrix | std::views::transform([] (const GeometricGraph::AdjacencyMatrixRow row) {
		return std::ranges::min(row);
	});
}

auto FindMinColumnsElements(const GeometricGraph::AdjacencyMatrix& adjacencyMatrix) {
	return std::views::iota(0ul, adjacencyMatrix.size()) | std::views::transform([adjacencyMatrix] (int columnNum) {
		return std::ranges::min(
			adjacencyMatrix
			| std::views::transform([columnNum] (const GeometricGraph::AdjacencyMatrixRow& row) {
				return row[columnNum];
			})
		);
	});
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
	if (++a >= 20) {
		return;
	}
	if (adjacencyMatrix.size() < 2) {
		if (!adjacencyMatrix.empty() && !adjacencyMatrix[0].empty() && bottomLimit < record) {
			record = bottomLimit;
			bestPath = path;
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
	auto minColumnsElements = FindMinColumnsElements(adjacencyMatrix);
	for (auto [columnNum, minElement] : std::views::zip(std::views::iota(0ul, adjacencyMatrix.size()), minColumnsElements)) {
		for (auto &row : adjacencyMatrix) {
			if (row[columnNum] != std::numeric_limits<double>::max())
				row[columnNum] -= minElement;
		}
	}

	bottomLimit +=
		+ Sum(minRowsElements)
		+ Sum(minColumnsElements);
	
	if (bottomLimit > record) {
		return;
	}

	auto penaltyMatrix = GetPenaltyMatrix(adjacencyMatrix, minRowsElements, minColumnsElements);
	auto maxPenalty = MaxOfMatrix(penaltyMatrix);
	tools::PrintMatrix(penaltyMatrix);
	std::cout << maxPenalty.value << " " << maxPenalty.i << " " << maxPenalty.j << std::endl;
	
	auto newMtx = MatrixReduction(maxPenalty.i, maxPenalty.j, adjacencyMatrix);
	auto newPath = path;
	newPath.emplace_back(maxPenalty.i, maxPenalty.j);
	FindHamiltonianCycle(newMtx, newPath, bestPath, record, bottomLimit);

	newMtx = adjacencyMatrix;
	newMtx[maxPenalty.i][maxPenalty.j] = std::numeric_limits<double>::max();
	FindHamiltonianCycle(newMtx, path, bestPath, record, bottomLimit);
}