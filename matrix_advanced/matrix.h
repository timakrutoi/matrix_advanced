#pragma once

#define _OUTPUT_PRECISION_ 5 // количетво знаков после запятой в операторе вывода
#define _OUTPUT_NUMBERSPACE_SIZE_ 4 // минимальный размер поля для вывода одного числа в операторе вывода
#define _THREADS_NUM_ 0

#include <iostream>
#include <future>
#include <ctime>
#include <iomanip>
//#include <vector>
//#include <immintrin.h>

std::mutex mtx;

template<typename T>
class matrix {
private:
	uint32_t size_x, size_y;
	T** data;

	const matrix add_zero() const; //similar to resize methods
	void cut(matrix& m1, matrix& m2, matrix& m3, matrix& m4);
	matrix cut(uint32_t size);
	void link(matrix& m1, matrix& m2, matrix& m3, matrix& m4);
public:
	matrix() { size_x = 0; size_y = 0; data = nullptr; };
	matrix(const matrix& m);//please see in comment on this method
	matrix(matrix&& m) noexcept;
	matrix(uint32_t row, uint32_t column);
	matrix(uint32_t size, char c = '0');//find bug, matrix<double> m_1(6,5); programm unknow what is 5, char or size_t
	~matrix();

	T& set(uint32_t x, uint32_t y, T value);
	void set(T val);
	void set();
	const T get(uint32_t x, uint32_t y) const;

	const uint32_t rows() const;
	const uint32_t columns() const;
	const void resize(uint32_t x, uint32_t y = x);//default y = x
	//const void resize(uint32_t x);//useless
	matrix without_row_and_col(uint32_t row, uint32_t col) const;
	matrix LU() const;

	const T det() const;
	const T minor(uint32_t row, uint32_t col) const;

	matrix inv();//need to optimization

	matrix operator+(const matrix& m) const;
	matrix operator-(const matrix& m) const;
	matrix& operator=(const matrix& m);//please see in comment on this method
	matrix& operator=(matrix&& m) noexcept;
	matrix operator*(const matrix& m) const;
	matrix operator*(const T& val) const;
	bool operator==(const matrix& m) const;
	matrix t();

	matrix multi(const matrix& m) const;//wrong rezult on rectangular matrices

	template <typename T>
	friend matrix<T> multi_strassen(const matrix<T>& m1, const matrix<T>& m2, short mlt_thread);//256
};

#include "matrix.ipp"