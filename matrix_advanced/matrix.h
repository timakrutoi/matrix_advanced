#pragma once

#define _OUTPUT_PRECISION_ 5 // количетво знаков после запятой в операторе вывода
#define _OUTPUT_NUMBERSPACE_SIZE_ 4 // минимальный размер поля для вывода одного числа в операторе вывода
#define _THREADS_NUM_ 0

#include <iostream>
#include <future>
#include <ctime>
#include <iomanip>
#include <vector>
//#include <immintrin.h>

std::mutex mtx;

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
	matrix(matrix&& m) noexcept;
	matrix(size_t row, size_t column);
	matrix(size_t size, char c = '0');
	~matrix();

	T& set(size_t x, size_t y, T value);
	void set(T val);
	void set();
	const T get(size_t x, size_t y) const;

	const size_t rows() const;
	const size_t columns() const;
	const void resize(size_t x, size_t y);
	const void resize(size_t x);
	matrix without_row_and_col(size_t row, size_t col) const;
	matrix LU() const;

	const T det() const;
	const T old_det() const;
	const T minor(size_t row, size_t col) const;

	matrix inv();

	matrix operator+(const matrix& m) const;
	matrix operator-(const matrix& m) const;
	matrix& operator=(const matrix& m);//починил этот метод
	matrix& operator=(matrix&& m) noexcept;//починил этот метод
	matrix operator*(const matrix& m) const;
	matrix operator*(const T& val) const;
	bool operator==(const matrix& m) const;
	matrix t();

	matrix multi(const matrix& m) const;//новый метод умножения

	template <typename T>
	friend matrix<T> multi_strassen(const matrix<T>& m1, const matrix<T>& m2, int mlt_thread); // надо правильно подобрать размерность матриц
};

//template<typename T>
//class matrix_new {
//private:
//	size_t size_x, size_y, size_all;
//	std::vector<T> data;
//	
//public:
//	matrix_new() { size_x = 0; size_y = 0; size_all = 0; };//It's working
//	matrix_new(size_t row, size_t column);//It's working
//	matrix_new(size_t size, char c = '0');//It's working
//	matrix_new(const matrix_new& m);//It's working
//
//	const T get(size_t row, size_t column) const;//It's working
//
//	const size_t rows() const;//It's working
//	const size_t columns() const;//It's working
//
//	matrix_new operator+(const matrix_new& m) const;//It's working
//	matrix_new operator-(const matrix_new& m) const;//It's working
//	matrix_new& operator=(const matrix_new& m);//It's working
//	matrix_new operator*(const matrix_new& m) const;
//	
//	bool operator==(const matrix<T>& m);
//	
//};

#include "matrix.ipp"