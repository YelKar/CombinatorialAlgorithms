#pragma once

#include <cmath>
#include <format>
#include <iostream>
#include <sstream>

template <typename T>
std::ostream& operator<<(std::ostream& os, MatrixRow<T> row_)
{
	unsigned int columnWidth = MatrixRow<T>::NumberLength(*std::max_element(row_.begin(), row_.end(), [](const T& a, const T& b) {
		return MatrixRow<T>::NumberLength(a) < MatrixRow<T>::NumberLength(b);
	}));
	return row_.stringify(os, columnWidth);
}

template <typename T>
std::function<std::ostream&(std::ostream&)> MatrixRow<T>::stringify(int columnWidth) const
{
	return [this, columnWidth](std::ostream& os) -> std::ostream& {
		return stringify(os, columnWidth);
	};
}

template <typename T>
std::ostream& MatrixRow<T>::stringify(std::ostream& os, int columnWidth) const
{
	os << "| ";
	for (T elt : *this)
	{
		os << std::format("{:{}} ", elt, columnWidth);
	}
	os << "|";
	return os;
}

template <typename T>
MatrixRow<T> MatrixRow<T>::operator*(T multiplier)
{
	MatrixRow<T> result = *this;
	for (T& elt : result)
	{
		elt *= multiplier;
	}
	return result;
}

template <typename T>
MatrixRow<T> MatrixRow<T>::operator*=(T multiplier)
{
	for (T& elt : *this)
	{
		elt *= multiplier;
	}
	return *this;
}

template <typename T>
MatrixRow<T> MatrixRow<T>::operator/(T divider)
{
	MatrixRow<T> result = *this;
	for (T& elt : result)
	{
		elt /= divider;
	}
	return result;
}

template <typename T>
MatrixRow<T> MatrixRow<T>::operator/=(T divider)
{
	for (T& elt : *this)
	{
		elt /= divider;
	}
	return *this;
}

template <typename T>
MatrixRow<T> MatrixRow<T>::operator+(const MatrixRow<T>& other) const
{
	MatrixRow<T> result;
	std::transform(
		this->begin(), this->end(),
		other.begin(), result.begin(),
		[](T a, T b) {
			return a + b;
		});
	return result;
}

template <typename T>
MatrixRow<T> MatrixRow<T>::operator+=(const MatrixRow<T>& other)
{
	std::transform(
		this->begin(), this->end(),
		other.begin(), this->begin(),
		[](T a, T b) {
			return a + b;
		});
	return *this;
}

template <typename T>
std::size_t MatrixRow<T>::NumberLength(T value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str().length();
}

template <typename T>
MatrixRow<T> MatrixRow<T>::operator-(const MatrixRow<T>& other) const
{
	MatrixRow<T> result;
	std::transform(
		this->begin(), this->end(),
		other.begin(),
		result.begin(),
		[](T a, T b) {
			return a - b;
		});
	return result;
}

template <typename T>
MatrixRow<T> MatrixRow<T>::operator-=(const MatrixRow<T>& other)
{
	std::transform(
		this->begin(), this->end(),
		other.begin(),
		this->begin(),
		[](T a, T b) {
			return a - b;
		});
	return *this;
}

template <typename T>
MatrixRow<T> MatrixRow<T>::operator-()
{
	MatrixRow<T> result;
	std::transform(
		this->begin(), this->end(),
		result.begin(),
		[](T a) {
			return -a;
		});
	return result;
}

inline std::ostream& operator<<(std::ostream& os, const std::function<std::ostream&(std::ostream&)>& manip)
{
	return manip(os);
}

