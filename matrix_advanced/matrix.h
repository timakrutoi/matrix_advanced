#pragma once

#define _OUTPUT_PRECISION_ 5 // êîëè÷åòâî çíàêîâ ïîñëå çàïÿòîé â îïåðàòîðå âûâîäà
#define _OUTPUT_NUMBERSPACE_SIZE_ 4 // ìèíèìàëüíûé ðàçìåð ïîëÿ äëÿ âûâîäà îäíîãî ÷èñëà â îïåðàòîðå âûâîäà
#define _THREADS_NUM_ 0

#include <iostream>
#include <future>
#include <ctime>
#include <iomanip>
//#include <vector>
//#include <immintrin.h>

template<typename T>
class matrix {
private:
	uint32_t size_x, size_y;
	T** data;

	const matrix add_zero() const; // similar to resize methods //needs some tests
	void cut(matrix& m1, matrix& m2, matrix& m3, matrix& m4);
	matrix cut(uint32_t size);
	void link(matrix& m1, matrix& m2, matrix& m3, matrix& m4);

public:
	matrix() { size_x = 0; size_y = 0; data = nullptr; };
	matrix(const matrix& m);
	matrix(matrix&& m) noexcept;
	matrix(uint32_t row, uint32_t column);
	matrix(uint32_t size);
	~matrix();

	void set(uint32_t x, uint32_t y, T value);
	void set(T val);
	void set();
	const T get(uint32_t x, uint32_t y) const;

	const uint32_t rows() const;
	const uint32_t columns() const;
	const void resize(uint32_t x, uint32_t y = x);
	matrix without_row_and_col(uint32_t row, uint32_t col) const;
	matrix LU() const;

	const T det() const;
	const T minor(uint32_t row, uint32_t col) const;

	matrix inv(); // needs some tests

	matrix operator+(const matrix& m) const;
	matrix operator-(const matrix& m) const;
	matrix& operator=(const matrix& m);
	matrix& operator=(matrix&& m) noexcept;
	matrix operator*(const matrix& m) const;
	matrix operator*(const T& val) const;
	bool operator==(const matrix& m) const;
	bool operator!=(const matrix& m) const;
	matrix t();

	matrix multi(const matrix& m) const; // use this only for square matrices //needs some tests

	static matrix<T> multi_strassen(const matrix<T>& m1, const matrix<T>& m2, short mlt_thread);
	
	static matrix<T> eye(uint32_t size);
};

#include "matrix.ipp"