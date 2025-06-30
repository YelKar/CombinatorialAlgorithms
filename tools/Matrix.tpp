#pragma once
#include <cassert>

template <typename T>
Matrix<T>::Matrix() {
	width = height = 1;
	MatrixRow<T> row;
	row.push_back(0);
	this->push_back(row);
};

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& mtx)
{
	if (mtx.size() == 0) {
		throw std::invalid_argument("Invalid initialized matrix size: matrix cannot has zero size");
	}
	for (
		auto initRow = mtx.begin();
		initRow != mtx.end();
		initRow++)
	{
		if (initRow->size() == 0) {
			throw std::invalid_argument("Invalid initialized matrix size: matrix cannot has zero size");
		}
		if (initRow->size() != mtx.begin()->size())
		{
			throw std::invalid_argument(
				"Invalid initialized matrix size: "
				"rows must have same sizes"
			);
		}
		MatrixRow<T> row;
		std::copy(initRow->begin(), initRow->end(), std::back_inserter(row));
		this->push_back(row);
	}
	height = this->size();
	width = this->operator[](0).size();
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T multiplier)
{
	Matrix<T> result = *this;
	for (MatrixRow<T>& elt : result)
	{
		elt *= multiplier;
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*=(T multiplier)
{
	for (MatrixRow<T>& elt : *this)
	{
		elt *= multiplier;
	}
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
	std::size_t m = height;
	std::size_t n = width;
	std::size_t p = other.width;
	if (n != other.size()) {
		throw std::invalid_argument("Invalid matrix for multiplying");
	}

	Matrix<T> result;
	result.clear();
	for (std::size_t i = 0; i < m; i++)
	{
		MatrixRow<T> row;
		for (std::size_t j = 0; j < p; j++)
		{
			row.push_back(this->GetElementMultiplicationResult(other, i, j));
		}
		result.push_back(row);
	}

	return result;
}

template <typename T>
T Matrix<T>::GetElementMultiplicationResult(const Matrix<T>& other, std::size_t i, std::size_t j) const
{
	std::size_t m = this->size();
	std::size_t p = other[0].size();
	if (i >= m || j >= p)
	{
		throw std::invalid_argument(std::format(
			"coordinates ({}; {}) must be less than result matrix size ({}; {})",
			i, j,
			m, p));
	}
	T result = 0;
	MatrixRow<T> row = this->operator[](i);
	for (auto [elt1, elt2] = std::tuple{ row.begin(), other.begin() }; elt1 != row.end(); elt1++, elt2++)
	{
		result += *elt1 * elt2->operator[](j);
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(T divider)
{
	Matrix<T> result = *this;
	for (MatrixRow<T>& elt : result)
	{
		elt /= divider;
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator/=(T divider)
{
	for (MatrixRow<T>& elt : *this)
	{
		elt /= divider;
	}
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other)
{
	if (this->size() != other.size() || this->operator[](0).size() != other[0].size()) {
		throw std::invalid_argument("Matrix must have same size during addition");
	}
	Matrix<T> result;
	std::transform(
		this->begin(), this->end(),
		other.begin(), result.begin(),
		[](const MatrixRow<T>& a, const MatrixRow<T>& b) {
			return a + b;
		});
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator+=(const Matrix<T>& other)
{
	if (this->size() != other.size() || this->operator[](0).size() != other[0].size()) {
		throw std::invalid_argument("Matrix must have same size during addition");
	}
	std::transform(
		this->begin(), this->end(),
		other.begin(), this->begin(),
		[](const MatrixRow<T>& a, const MatrixRow<T>& b) {
			return a + b;
		});
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other)
{
	if (this->size() != other.size() || this->operator[](0).size() != other[0].size()) {
		throw std::invalid_argument("Matrix must have same size during the subtraction");
	}
	Matrix<T> result;
	std::transform(
		this->begin(), this->end(),
		other.begin(), result.begin(),
		[](MatrixRow<T>& a, MatrixRow<T>& b) {
			return a - b;
		});
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-=(const Matrix<T>& other)
{
	if (this->size() != other.size() || this->operator[](0).size() != other[0].size()) {
		throw std::invalid_argument("Matrix must have same size during the subtraction");
	}
	std::transform(
		this->begin(), this->end(),
		other.begin(), this->begin(),
		[](const MatrixRow<T>& a, const MatrixRow<T>& b) {
			return a - b;
		});
	return *this;
}

template <typename T>
template <typename TT>
Matrix<T>::operator Matrix<TT>()
{
	Matrix<TT> result;
	result.clear();
	for (std::size_t i = 0; i < height; i++)
	{
		MatrixRow<TT> row;
		for (std::size_t j = 0; j < width; j++)
		{
			row.push_back(static_cast<TT>((*this)[i][j]));
		}
		result.push_back(row);
	}
	result.width = width;
	result.height = height;
	return result;
}

template <typename T>
T Matrix<T>::DeterminantByPermutation() const
{
	std::size_t m = this->size();
	std::size_t n = this->operator[](0).size();
	if (n != m)
	{
		throw std::invalid_argument("Not square matrix has no determinant");
	}
	return CalculateDeterminantByPermutations();
}

template <typename T>
T Matrix<T>::CalculateDeterminantByPermutations() const
{
	const std::size_t size = this->size();
	auto matrix = *this;

	if (size == 1)
	{
		return matrix[0][0];
	}

	if (size == 2)
	{
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}

	std::vector<std::size_t> permutation(size);
	for (std::size_t i = 0; i < size; ++i)
	{
		permutation[i] = i;
	}

	T determinant = 0;

	do
	{
		T product = 1;
		int inversions = 0;

		for (std::size_t i = 0; i < size; ++i)
		{
			product *= matrix[i][permutation[i]];
			for (std::size_t j = 0; j < i; ++j)
			{
				if (permutation[j] > permutation[i])
				{
					inversions++;
				}
			}
		}

		if (inversions % 2 == 0)
		{
			determinant += product;
		}
		else
		{
			determinant -= product;
		}

	} while (std::next_permutation(permutation.begin(), permutation.end()));

	return determinant;
}

template <typename T>
T Matrix<T>::Determinant() const
{
	if (width < 1 || height < 1)
	{
		throw std::invalid_argument("Size must be positive");
	}
	if (width != height)
	{
		throw std::invalid_argument("Not square matrix has no determinant");
	}
	return CalculateDeterminantByPermutations();
}

template <typename T>
T Matrix<T>::CalculateDeterminant() const
{
	double determinant = 1;
	auto upperTriangularMtx = UpperTriangularForm();

	for (int i = 0; i < height; i++)
	{
		determinant *= upperTriangularMtx[i][i];
	}

	return static_cast<T>(determinant);
}

template <typename T>
Matrix<double> Matrix<T>::UpperTriangularForm() const
{
	if (width < 1 || height < 1)
	{
		throw std::invalid_argument("Size must be positive");
	}
	if (width != height)
	{
		throw std::invalid_argument("Not square matrix has no upper triangular form");
	}
	Matrix<double> matrix;

	for (int i = 0; auto& row : matrix)
	{
		for (int j = 0; auto& elt : row)
		{
			elt = static_cast<double>((*this)[i][j]);
			j++;
		}
		i++;
	}

	for (auto& row : matrix)
	{
		for (double& elt : row)
		{
			elt = std::round(elt * std::pow(10, 10)) / std::pow(10, 10);
		}
	}
	return matrix;
}

template <typename T>
T Matrix<T>::AlgebraicAddition(std::size_t i, std::size_t j) const
{
	if (width < 1 || height < 1)
	{
		throw std::invalid_argument("Size must be positive");
	}
	return Minor(i, j) * static_cast<T>(std::pow(-1, i + j));
}

template <typename T>
Matrix<T> Matrix<T>::MinorMatrix(std::size_t i_, std::size_t j_) const
{
	if (width < 2 || height < 2)
	{
		throw std::invalid_argument("Too small matrix");
	}
	Matrix<T> result;
	result.clear();
	for (std::size_t i = 0; i < height - 1; i++)
	{
		MatrixRow<T> row;
		for (std::size_t j = 0; j < width - 1; j++)
		{
			row.push_back((*this)[i + (i >= i_)][j + (j >= j_)]);
		}
		result.push_back(row);
	}
	return result;
};

template <typename T>
T Matrix<T>::Minor(std::size_t i, std::size_t j) const
{
	return MinorMatrix(i, j).DeterminantByPermutation();
}

template <typename T>
Matrix<T> Matrix<T>::Transposed() const
{
	Matrix<T> result;
	result.clear();

	for (std::size_t j = 0; j < width; j++)
	{
		MatrixRow<T> row;
		for (std::size_t i = 0; i < height; i++)
		{
			row.push_back((*this)[i][j]);
		}
		result.push_back(row);
	}
	result.width = height;
	result.height = width;

	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator^(int p) const
{
	if (width != height)
	{
		throw std::invalid_argument("Non-square matrix cannot be raised to a power");
	}
	if (p == 0)
	{
		return IdentityMatrix();
	}
	Matrix<T> matrix = p > 0 ? *this : InvertedMatrix();
	Matrix<T> multiplier = matrix;
	for (int i = 1; i < std::abs(p); i++)
	{
		matrix = matrix * multiplier;
	}
	return matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator^=(int p)
{
	return *this ^ p;
}

template <typename T>
Matrix<T> Matrix<T>::AdjointMatrix() const
{
	Matrix<T> result = *this;

	for (std::size_t i = 0; auto& row : result)
	{
		for (std::size_t j = 0; auto& elt : result)
		{
			result[i][j] = AlgebraicAddition(i, j);
			j++;
		}
		i++;
	}

	return result;
}

template <typename T>
Matrix<T> Matrix<T>::InvertedMatrix() const
{
	std::cout << AdjointMatrix().Transposed().stringify(3) << std::endl;
	return AdjointMatrix().Transposed() / DeterminantByPermutation();
}

template <typename T>
std::function<std::ostream&(std::ostream&)> Matrix<T>::stringify(int columnWidth) const
{
	return [this, columnWidth](std::ostream& os) -> std::ostream& {
		return stringify(os, columnWidth);
	};
	;
}

template <typename T>
std::ostream& Matrix<T>::stringify(std::ostream& os, int columnWidth) const
{
	for (const MatrixRow<T>& row : *this)
	{
		row.stringify(os, columnWidth) << std::endl;
	}
	return os;
}

template <typename T>
Matrix<T> Matrix<T>::IdentityMatrix(std::size_t m, std::size_t n)
{
	Matrix<T> result;
	if (n != m)
	{
		throw std::invalid_argument("The identity matrix must be square");
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			result[i][j] = T(i == j);
		}
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::IdentityMatrix()
{
	return IdentityMatrix(height, width);
}