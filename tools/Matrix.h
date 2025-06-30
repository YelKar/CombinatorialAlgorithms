#pragma once

#include "MatrixRow.h"
#include <vector>

template <typename T>
class Matrix : public std::vector<MatrixRow<T>>
{
public:
	Matrix();
	Matrix(const std::initializer_list<std::initializer_list<T>>& mtx);
	Matrix<T> operator*(T);
	Matrix<T> operator*=(T);
	Matrix<T> operator*(const Matrix<T>&) const;
	Matrix<T> operator/(T);
	Matrix<T> operator/=(T);
	Matrix<T> operator+(const Matrix<T>&);
	Matrix<T> operator+=(const Matrix<T>&);
	Matrix<T> operator-(const Matrix<T>&);
	Matrix<T> operator-=(const Matrix<T>&);
	Matrix<T> operator^(int p) const;
	Matrix<T> operator^=(int p);
	[[nodiscard]] Matrix<T> MinorMatrix(std::size_t i, std::size_t j) const;
	[[nodiscard]] T Minor(std::size_t i, std::size_t j) const;
	[[nodiscard]] T Determinant() const;
	[[nodiscard]] T DeterminantByPermutation() const;
	[[nodiscard]] T AlgebraicAddition(std::size_t i, std::size_t j) const;
	[[nodiscard]] Matrix<T> Transposed() const;
	static Matrix<T> IdentityMatrix(std::size_t m, std::size_t n);
	Matrix<T> IdentityMatrix();
	[[nodiscard]] std::function<std::ostream&(std::ostream&)> stringify(int columnWidth) const;
	std::ostream& stringify(std::ostream& os, int columnWidth) const;
	[[nodiscard]] Matrix<double> UpperTriangularForm() const;
	[[nodiscard]] Matrix<T> AdjointMatrix() const;
	[[nodiscard]] Matrix<T> InvertedMatrix() const;
	template <typename TT>
	operator Matrix<TT>(); // NOLINT

	std::size_t width, height;
private:
	[[nodiscard]] T GetElementMultiplicationResult(const Matrix<T>&, std::size_t i, std::size_t j) const;
	[[nodiscard]] T CalculateDeterminant() const;
	[[nodiscard]] T CalculateDeterminantByPermutations() const;
};

#include "Matrix.tpp"
