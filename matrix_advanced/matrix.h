#pragma once

#define _THREAD_NUMBER_ 1 // семь в степени этого числа потоков + 1 основной для мейна
#define _OUTPUT_PRECISION_ 0 // количетво знаков после запятой в операторе вывода

#include <iostream>
#include <future>
#include <ctime>
#include <iomanip>

template<typename T>
class matrix {
private:
	size_t size_x, size_y;
	T** data;

	const matrix add_zero() const;
	void cut(matrix& m1, matrix& m2, matrix& m3, matrix& m4);
	matrix cut(size_t size);
	void link(matrix& m1, matrix& m2, matrix& m3, matrix& m4);
public:
	matrix() { size_x = 0; size_y = 0; data = nullptr; };
	matrix(const matrix& m);
	matrix(size_t row, size_t column);
	matrix(size_t size, char c = '0');
	~matrix();

	T& set(size_t x, size_t y, T value);
	void set(T val);
	void set();
	const T get(size_t x, size_t y) const;

	const size_t rows() const;
	const size_t columns() const;
	matrix without_row_and_col(size_t row, size_t col) const;
	matrix LU() const;

	const T det() const;
	const T old_det() const;
	const T minor(size_t row, size_t col) const;

	matrix inv();

	matrix operator+(const matrix& m) const;
	matrix operator-(const matrix& m) const;
	matrix& operator=(const matrix& m);
	matrix operator*(const matrix& m) const;
	matrix operator*(const T& val) const;
	bool operator==(const matrix& m) const;
	matrix t();

	template <typename T>
	friend matrix<T> multi_strassen(const matrix<T>& m1, const matrix<T>& m2, int mlt_thread);
};

#include "matrix.ipp"