#pragma once

#include <format>
#include <functional>
#include <ostream>
#include <vector>

template <typename T>
class MatrixRow : public std::vector<T>
{
public:
	MatrixRow<T> operator*(T);
	MatrixRow<T> operator*=(T);
	MatrixRow<T> operator/(T);
	MatrixRow<T> operator/=(T);
	MatrixRow<T> operator+(const MatrixRow<T>&) const;
	MatrixRow<T> operator+=(const MatrixRow<T>&);
	MatrixRow<T> operator-(const MatrixRow<T>&) const;
	MatrixRow<T> operator-=(const MatrixRow<T>&);
	MatrixRow<T> operator-();
	template <std::size_t N_, typename T_>
	friend std::ostream& operator<<(std::ostream&, MatrixRow<T_>);
	[[ nodiscard ]] std::function<std::ostream&(std::ostream&)> stringify(int columnWidth) const;
	std::ostream& stringify(std::ostream& os, int columnWidth) const;
private:
	static std::size_t NumberLength(T value);
};

std::ostream& operator<<(std::ostream& os, const std::function<std::ostream&(std::ostream&)>& manip);

#include "MatrixRow.tpp"
