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
		for (int j = 0; i < adjacencyMatrix.size(); ++j) {
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
			if (matrix[i][j] > result.value) {
				result = {
					matrix[i][j],
					i, j,
				};
			}
		}
	}
	return result;
}