#include "matrix.h"
template<typename T>
inline matrix<T>::matrix(size_t row, size_t column) {
	size_x = row; size_y = column;
	data = new T * [size_x];

	try {
		data[0] = new T[size_x * size_y];
	}
	catch (const std::bad_alloc&) {
		delete[] data;
		throw;
	}

	std::fill_n(data[0], size_x * size_y, 0);
	for (size_t i = 1; i < size_x; i++) {
		data[i] = data[0] + i * size_y;
	}
}

template <typename T>
matrix<T>::matrix(size_t size, char c) {
	size_x = size; size_y = size;
	data = new T * [size_x];

	try {
		data[0] = new T[size_x * size_y];
	}
	catch (const std::bad_alloc&) {
		delete[] data;
		throw;
	}

	std::fill_n(data[0], size_x * size_y, 0);
	if (c == 'e')
		for (size_t i = 1; i < size_x; i++) {
			data[i] = data[0] + i * size_y;
			data[i][i] = 1;
		}
	else 
		for (size_t i = 1; i < size_x; i++) {
			data[i] = data[0] + i * size_y;
		}
}

template<typename T>
matrix<T>::matrix(const matrix& m) {
	size_x = m.size_x; size_y = m.size_y;
	size_t temp_size = size_x * size_y;
	data = new T * [size_x];

	try {
		data[0] = new T[temp_size];
	}
	catch (const std::bad_alloc&) {
		delete[] data;
		throw;
	}

	for (size_t i = 0; i < temp_size; i++) {
		if (i % size_y == 0 || i == 0) data[i / size_y] = data[0] + i;

		data[i / size_y][i % size_y] = m.data[i / size_y][i % size_y];
	}
}

template<typename T>
matrix<T>::matrix(matrix&& m) noexcept {
	size_x = m.size_x; m.size_x = 0;
	size_y = m.size_y; m.size_y = 0;
	data = m.data;
	m.data = nullptr;
}

template<typename T>
T& matrix<T>::set(size_t row, size_t column, T value) {
	if (row >= size_x || column >= size_y) throw std::out_of_range("Invalid args( set )");

	data[row][column] = value;
	return data[row][column];
}

template<typename T>
void matrix<T>::set(T val) {
	for (size_t i = 0; i < size_x; i++) {
		std::fill_n(data[i], size_y, val);
	}
}

template<typename T>
void matrix<T>::set() {
	srand(12342);
	for (size_t i = 0; i < size_x; i++) {
		for (size_t j = 0; j < size_y; j++) {
			data[i][j] = /*T(rand() % 9) + */1;
		}
	}
}

template<typename T>
const T matrix<T>::get(size_t row, size_t column) const {
	if (row >= size_x || column >= size_y) throw std::out_of_range("Invalid args ( get )");

	return data[row][column];
}

template<typename T>
const size_t matrix<T>::rows() const {
	return size_x;
}

template<typename T>
const size_t matrix<T>::columns() const {
	return size_y;
}

template<typename T>
const void matrix<T>::resize(size_t x, size_t y) {
	matrix<T> temp(x, y);

	for (size_t i = 0; i < size_x; i++) {
		for (size_t j = 0; j < size_y; j++) {
			if (i < x && j < y) temp.data[i][j] = data[i][j];
		}
	}

	*this = temp;
	//return temp;
}

template<typename T>
const void matrix<T>::resize(size_t x) {
	matrix<T> temp(x);

	for (size_t i = 0; i < size_x; i++) {
		for (size_t j = 0; j < size_x; j++) {
			if (i < x && j < x) temp.data[i][j] = data[i][j];
		}
	}

	*this = temp;
	//return temp;
}

template <typename T>
const matrix<T> matrix<T>::add_zero() const {
	if (!size_x || !size_y) throw std::logic_error("Invalid size in add_zero");
	size_t size = 1;
	while (size < size_x) {
		size <<= 1;
	}

	matrix<T> temp(size, size);

	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			if (i < size_x && j < size_y) temp.data[i][j] = data[i][j];
			else temp.data[i][j] = T(0);
		}
	}

	return temp;
}

template <typename T>
void matrix<T>::cut(matrix<T>& m1, matrix<T>& m2, matrix<T>& m3, matrix<T>& m4) {
	if (m1.size_x != (size_x / 2) || m1.size_y != (size_y / 2) ||
		m2.size_x != (size_x / 2) || m2.size_y != (size_y / 2) ||
		m3.size_x != (size_x / 2) || m3.size_y != (size_y / 2) ||
		m4.size_x != (size_x / 2) || m4.size_y != (size_y / 2)) throw std::logic_error("Invalid sizes in cut");

	size_t temp_x = size_x / 2; 
	size_t temp_y = temp_x;
	 
	int size = size_x * size_x;
	for (int i = 0; i < size; i++) {
		if (i / size_x < temp_x && i % size_x < temp_y) m1.data[i / size_x][i % size_x] = data[i / size_x][i % size_x];
		if (i / size_x < temp_x && i % size_x >= temp_y) m2.data[i / size_x][i % size_x - temp_y] = data[i / size_x][i % size_x];
		if (i / size_x >= temp_x && i % size_x < temp_y) m3.data[i / size_x - temp_x][i % size_x] = data[i / size_x][i % size_x];
		if (i / size_x >= temp_x && i % size_x >= temp_y) m4.data[i / size_x - temp_x][i % size_x - temp_y] = data[i / size_x][i % size_x];
	}
	/*for (size_t i = 0; i < size_x; i++) {
		for (size_t j = 0; j < size_x; j++) {
			if (i < temp_x && j < temp_y) m1.data[i][j] = data[i][j];
			if (i < temp_x && j >= temp_y) m2.data[i][j - temp_y] = data[i][j];
			if (i >= temp_x && j < temp_y) m3.data[i - temp_x][j] = data[i][j];
			if (i >= temp_x && j >= temp_y) m4.data[i - temp_x][j - temp_y] = data[i][j];
		}
	}*/
}

template <typename T>
matrix<T> matrix<T>::cut(size_t size) {
	matrix<T> temp(size);
	int tmp_size = size * size;

	for (size_t i = 0; i < tmp_size; i++) {
		temp.data[i / size][i % size] = data[i / size][i % size];
	}

	return temp;
}

template <typename T>
void matrix<T>::link(matrix<T>& m1, matrix<T>& m2, matrix<T>& m3, matrix<T>& m4) {
	if (m1.size_x != (size_x / 2) && m1.size_y != (size_y / 2) &&
		m2.size_x != (size_x / 2) && m2.size_y != (size_y / 2) &&
		m3.size_x != (size_x / 2) && m3.size_y != (size_y / 2) &&
		m4.size_x != (size_x / 2) && m4.size_y != (size_y / 2)) throw std::logic_error("Invalid sizes in link");

	size_t temp_x = size_x / 2, temp_y = size_y / 2;

	for (size_t i = 0; i < size_x; i++) {
		for (size_t j = 0; j < size_x; j++) {
			if (i < temp_x && j < temp_y) data[i][j] = m1.data[i][j];
			if (i < temp_x && j >= temp_y) data[i][j] = m2.data[i][j - temp_y];
			if (i >= temp_x && j < temp_y) data[i][j] = m3.data[i - temp_x][j];
			if (i >= temp_x && j >= temp_y) data[i][j] = m4.data[i - temp_x][j - temp_y];
		}
	}
}

template<typename T>
matrix<T> matrix<T>::without_row_and_col(size_t row, size_t col) const {
	if (!(row < size_x && col < size_y)) throw std::logic_error("Invalid sizes in without_row_and_col");
	matrix<T> temp(size_x - 1, size_y - 1);

	for (size_t i = 0, c = 0; i < temp.size_x; i++, c++) {
		for (size_t j = 0, v = 0; j < temp.size_y; j++, v++) {
			if (c == row) c++;
			if (v == col) v++;

			temp.data[i][j] = data[c][v];
		}
	}

	return temp;
}

template<typename T>
matrix<T> matrix<T>::LU() const{
	if (!(size_x == size_y) || data[0][0] == 0) throw std::logic_error("Invalid matrix in LU");

	matrix<T> L(size_x), U(size_x);
	//size_t c = 0;

	for (size_t i = 0; i < size_x; i++) {
		U.data[0][i] = data[0][i];
		L.data[i][0] = (data[i][0] / data[0][0]);
	}

	for (size_t i = 1; i < size_x; i++) {
		for (size_t j = i; j < size_x; j++) {

			U.data[i][j] = data[i][j];
			L.data[j][i] = data[j][i];

			for (size_t k = 0; k < i; k++) {
				U.data[i][j] = U.data[i][j] - (L.data[i][k] * U.data[k][j]);
				L.data[j][i] = L.data[j][i] - (L.data[j][k] * U.data[k][i]);
				//c++;
			}

			L.data[j][i] = L.data[j][i] / U.data[i][i];
		}
	}
	//std::cout << c << std::endl;

	return U;
}

template<typename T>
const T matrix<T>::old_det() const {
	if (size_x != size_y) throw std::logic_error("Invalid matrix size in det");
	T result = 0;

	if (size_x > 2) {
		for (size_t i = 0; i < size_x; i++) {
			matrix<T> temp = this->without_row_and_col(0, i);
			result = result + T(pow(-1, i) * data[0][i] * temp.old_det());
		}
		return result;
	}
	else return T(data[0][0] * data[1][1] - data[0][1] * data[1][0]);
}

template<typename T>
const T matrix<T>::det() const {
	if (size_x != size_y) throw std::logic_error("Invalid matrix size in det");
	matrix<T> temp(*this); temp = temp.LU();
	T det = T(1);

	for (size_t i = 0; i < size_x; i++) {
		det = det * temp.data[i][i];
	}

	return det;
}

template<typename T>
const T matrix<T>::minor(size_t row, size_t col) const {
	matrix<T> temp = this->without_row_and_col(row, col);

	return temp.det();
}

template<typename T>
matrix<T> matrix<T>::inv() {
	if (size_x != size_y) throw std::logic_error("Invalid matrix size in inverse matrix");

	matrix<T> E(size_x, 'e'); //E.set_E();
	matrix<T> copy(*this);

	for (size_t k = 0; k < size_x; k++) {
		if (copy.data[k][k] == 0) {
			size_t i = 0;

			for (i; i < size_x || copy.data[i][k] != 0; i++);

			for (size_t j = 0; j < size_x; j++) {
				T tmp = copy.data[k][j];
				copy.data[k][j] = copy.data[i][j];
				copy.data[i][j] = tmp;
				tmp = E.data[k][j];
				E.data[k][j] = E.data[i][j];
				E.data[i][j] = tmp;
			}
		}

		if (copy.data[k][k] != 1) {
			T coe = (T) 1 / copy.data[k][k];

			for (size_t i = 0; i < size_x; i++) {
				copy.data[k][i] = copy.data[k][i] * coe;
				E.data[k][i] = E.data[k][i] * coe;
			}
		}

		for (size_t i = 0; i < size_x; i++) {
			if (i == k) continue;
			double coe = copy.data[i][k];

			for (size_t j = 0; j < size_x; j++) {
				copy.data[i][j] = copy.data[i][j] - (coe * copy.data[k][j]);
				E.data[i][j] = E.data[i][j] - (coe * E.data[k][j]);
			}
		}
	}

	return E;
}

template<typename T>
matrix<T> matrix<T>::operator+(const matrix& m) const {
	if (!(size_x == m.size_x && size_y == m.size_y)) throw std::logic_error("Matrices must be equal sizes to do '+'");

	matrix<T> temp(size_x, size_y);
	size_t temp_size = size_x * size_y;

	for (size_t i = 0; i < temp_size; i++) {
		temp.data[i / size_y][i % size_y] = data[i / size_y][i % size_y] + m.data[i / size_y][i % size_y];
	}

	return temp;
}

template<typename T>
matrix<T> matrix<T>::operator-(const matrix& m) const {
	if (!(size_x == m.size_x && size_y == m.size_y)) throw std::logic_error("Matrices must be equal sizes to do '+'");

	matrix<T> temp(size_x, size_y);
	size_t temp_size = size_x * size_y;

	for (size_t i = 0; i < temp_size; i++) {
		temp.data[i / size_y][i % size_y] = data[i / size_y][i % size_y] - m.data[i / size_y][i % size_y];
	}

	return temp;
}

template<typename T>
matrix<T>& matrix<T>::operator=(matrix&& m) noexcept {
	if (this == &m) return *this;
	if (data) { // этот момент взят из деструктора
		delete[] data[0];
		delete[] data;
		data = nullptr;
	}

	size_x = m.size_x; m.size_x = 0;
	size_y = m.size_y; m.size_y = 0;
	data = m.data;
	m.data = nullptr;

	return *this;
}

template<typename T>
matrix<T>& matrix<T>::operator=(const matrix& m) {
	if (this == &m) return *this;
	if (data) {// этот момент взят из деструктора
		delete[] data[0];
		delete[] data;
		data = nullptr;
	}
	size_x = m.size_x; size_y = m.size_y;
	size_t temp_size = size_x * size_y;
	data = new T * [size_x];

	try {
		data[0] = new T[temp_size];
	}
	catch (const std::bad_alloc&) {
		delete[] data[0];
		throw;
	}

	for (size_t i = 0; i < temp_size; i++) {
		if (i % size_y == 0 || i == 0) data[i / size_y] = data[0] + i;

		data[i / size_y][i % size_y] = m.data[i / size_y][i % size_y];
	}

	return *this;
}

template<typename T>
bool matrix<T>::operator==(const matrix<T>& m) const {
	if (size_x != m.size_x || size_y != m.size_y) return false;

	for (size_t i = 0; i < size_x; i++) {
		for (size_t j = 0; j < size_y; j++) {
			if (!(data[i][j] == m.data[i][j])) return false;
		}
	}

	return true;
}

template<typename T>
matrix<T> matrix<T>::operator*(const matrix& m) const {
	if (size_y != m.size_x) throw std::logic_error("Invalid operator *");

	//if (size_x >= 64) return multi_strassen(*this, m, 1);

	matrix<T> temp(size_x, m.size_y);

	for (size_t i = 0; i < size_x; i++) {
		for (size_t j = 0; j < m.size_y; j++) {
			for (size_t k = 0; k < size_y; k++) {
				temp.data[i][j] += data[i][k] * m.data[k][j];
			}
		}
	}

	return temp;
}

template<typename T>
matrix<T> matrix<T>::operator*(const T& val) const {
	matrix<T> temp(*this);

	for (size_t i = 0; i < size_x; i++) {
		for (size_t j = 0; j < size_y; j++) {
			temp.data[i][j] = temp.data[i][j] * val;
		}
	}

	return temp;
}

template <typename T>
matrix<T> multi_strassen(const matrix<T>& m1, const matrix<T>& m2, int mlt_thread) {

	matrix<T> temp1 = m1.add_zero(), temp2 = m2.add_zero();
	size_t out_size = m1.size_x;
	size_t size = temp1.size_x;

	if (size <= 256) {//надо правильно подобрать значение
		return m1.multi(m2);
	}

	matrix<T> out(size);
	size >>= 1;

	matrix<T> a1(size), a2(size), a3(size), a4(size);
	matrix<T> b1(size), b2(size), b3(size), b4(size);
	
	temp1.cut(a1, a2, a3, a4);
	temp2.cut(b1, b2, b3, b4);

	matrix<T> p1, p2, p3, p4, p5, p6, p7;

	if (mlt_thread > 0) {
		mlt_thread--;
		
		std::future<matrix<T>> f1 = std::async(&multi_strassen<T>, a1, b2 - b4, mlt_thread);
		std::future<matrix<T>> f2 = std::async(&multi_strassen<T>, a1 + a2, b4, mlt_thread);
		std::future<matrix<T>> f3 = std::async(&multi_strassen<T>, a3 + a4, b1, mlt_thread);
		std::future<matrix<T>> f4 = std::async(&multi_strassen<T>, a4, b3 - b1, mlt_thread);
		std::future<matrix<T>> f5 = std::async(&multi_strassen<T>, a1 + a4, b1 + b4, mlt_thread);
		std::future<matrix<T>> f6 = std::async(&multi_strassen<T>, a2 - a4, b3 + b4, mlt_thread);
		std::future<matrix<T>> f7 = std::async(&multi_strassen<T>, a1 - a3, b1 + b2, mlt_thread);

		p1 = f1.get();
		p2 = f2.get();
		p3 = f3.get();
		p4 = f4.get();
		p5 = f5.get();
		p6 = f6.get();
		p7 = f7.get();
	}
	else {
		p1 = multi_strassen(a1, b2 - b4, mlt_thread);
		p2 = multi_strassen(a1 + a2, b4, mlt_thread);
		p3 = multi_strassen(a3 + a4, b1, mlt_thread);
		p4 = multi_strassen(a4, b3 - b1, mlt_thread);
		p5 = multi_strassen(a1 + a4, b1 + b4, mlt_thread);
		p6 = multi_strassen(a2 - a4, b3 + b4, mlt_thread);
		p7 = multi_strassen(a1 - a3, b1 + b2, mlt_thread);
	}

	matrix<T> c1 = (p5 + p4) + (p6 - p2);
	matrix<T> c2 = (p1 + p2);
	matrix<T> c3 = (p3 + p4);
	matrix<T> c4 = (p1 - p3) + (p5 - p7);
	
	out.link(c1, c2, c3, c4);
	out = out.cut(m1.size_x);

	return out;
}

template <typename T>
matrix<T> matrix<T>::t() {
	matrix<T> temp(size_y, size_x);

	for (size_t i = 0; i < size_y; i++) {
		for (size_t j = 0; j < size_x; j++) {
			temp.data[i][j] = data[j][i];
		}
	}

	return temp;
}

template<typename T>
inline matrix<T> matrix<T>::multi(const matrix& m) const{
	matrix<T> out(m.size_x, size_y);
	for (int i = 0; i < size_y; ++i){
		T* c = out.data[i];
		for (int k = 0; k < size_x; ++k){
			const T* b = m.data[k];
			T a = data[i][k];
			for (int j = 0; j < m.size_x; ++j)
				c[j] += a * b[j];
		}
	}
	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, matrix<T>& matrix) {
	out << "[ ";
	size_t size = matrix.columns() * matrix.rows();
	//std::cout.precision(_OUTPUT_PRECISION_);

	for (size_t i = 0; i < size; i++) {
		size_t n = 0;
		if (i % matrix.rows() == 0 && i > 0) out << "]\n[ ";
		if (!(matrix.get(i / matrix.columns(), i % matrix.columns()) < 0) && n <= 4) { out << " "; n++; }
		out << std::setw(_OUTPUT_PRECISION_ + _OUTPUT_NUMBERSPACE_SIZE_ - n) << std::setprecision(_OUTPUT_PRECISION_) << std::left << matrix.get(i / matrix.columns(), i % matrix.columns()) << " ";
	}
	out << "]" << std::endl;

	return out;
}

template<typename T>
matrix<T>::~matrix() {
	if (!data) return;

	delete[] data[0];
	delete[] data;

	data = nullptr;
}

//matrix on vector
//
//template<typename T>
//inline matrix_new<T>::matrix_new(size_t row, size_t column){
//	size_x = column;
//	size_y = row;
//	size_all = row * column;
//	data.resize(size_all, (T)0);
//}
//
//template<typename T>
//inline matrix_new<T>::matrix_new(size_t size, char c){
//	size_x = size;
//	size_y = size;
//	size_all = size * size;
//	if (c == '1') {
//		data.resize(size_all, (T)1);
//		return;
//	}
//	data.resize(size_all, (T)0);
//	if (c == 'r') {
//		srand(12342);//swap on clock()
//		for (size_t i = 0; i < size_all; i++)
//			data[i] = T(rand() % 9) + 1;
//		return;
//	}
//	if (c == 'I') {
//		size_t tmp = size + 1;
//		for (size_t i = 0; i < size; i++)
//			data[i * tmp] = 1;
//		return;
//	}
//}
//
//template<typename T>
//inline matrix_new<T>::matrix_new(const matrix_new& m){
//	size_x = m.size_x;
//	size_y = m.size_y;
//	size_all = size_x * size_y;
//	data = m.data;
//}
//
//template<typename T>
//inline const T matrix_new<T>::get(size_t row, size_t column) const{
//	if (row * column > size_all || row * column < 0) throw std::out_of_range("Invalid args ( get )");
//	return data[row * size_y + column];
//}
//
//template<typename T>
//inline const size_t matrix_new<T>::rows() const{
//	return size_y;
//}
//
//template<typename T>
//inline const size_t matrix_new<T>::columns() const{
//	return size_x;
//}
//
//template<typename T>
//inline matrix_new<T> matrix_new<T>::operator+(const matrix_new& m) const{
//	if (size_x != m.size_x || size_y != m.size_y) throw std::logic_error("Matrices must be equal sizes to do '+'");
//	matrix_new<T> tmp(*this);
//	for (size_t i = 0; i < size_all; i++) 
//		tmp.data[i] += m.data[i];
//	return tmp;
//}
//
//template<typename T>
//inline matrix_new<T> matrix_new<T>::operator-(const matrix_new& m) const {
//	if (size_x != m.size_x || size_y != m.size_y) throw std::logic_error("Matrices must be equal sizes to do '+'");
//	matrix_new<T> tmp(*this);
//	for (size_t i = 0; i < size_all; i++)
//		tmp.data[i] -= m.data[i];
//	return tmp;
//}
//
//template<typename T>
//inline matrix_new<T>& matrix_new<T>::operator=(const matrix_new& m){
//	if (this == &m) return *this;
//	size_x = m.size_x;
//	size_y = m.size_y;
//	size_all = m.size_all;
//	data = m.data;
//	return *this;
//}
//
//template<typename T>
//inline matrix_new<T> matrix_new<T>::operator*(const matrix_new& m) const{
//	matrix_new<T> out(size_x, size_y);
//	std::vector<T> thatColumn(m.size_y);
//	for (size_t j = 0; j < m.size_x; j++) {
//		int tmp_j = j * size_x;
//		for (size_t k = 0; k < size_x; k++) {
//			thatColumn[k] = m.data[k * m.size_x + j];
//		}
//
//		for (size_t i = 0; i < size_y; i++) {
//			std::vector<T> thisRow(size_x);
//			int tmp_i = i * size_x;
//			for (size_t k = 0; k < size_x; k++)
//				thisRow[k] = data[tmp_i + k];
//			double summand = 0;
//			for (size_t k = 0; k < size_x; k++) {
//				summand += thisRow[k] * thatColumn[k];
//			}
//			out.data[tmp_j + i] = summand;
//		}
//	}
//	return out;
//}
//
//template<typename T>
//inline bool matrix_new<T>::operator==(const matrix<T>& m){
//	if (size_x != m.rows() || size_y != m.columns()) return false;
//	for (size_t i = 0; i < size_all; i++)
//		if (data[i] != m.get(i / size_x, i % size_y)) return false;
//	return true;
//}
//
//template<typename T>
//std::ostream& operator<<(std::ostream& out, matrix_new<T>& matrix) {
//	out << "[ ";
//	size_t size = matrix.columns() * matrix.rows();
//	//std::cout.precision(_OUTPUT_PRECISION_);
//
//	for (size_t i = 0; i < size; i++) {
//		size_t n = 0;
//		if (i % matrix.rows() == 0 && i > 0) out << "]\n[ ";
//		if (!(matrix.get(i / matrix.columns(), i % matrix.columns()) < 0) && n <= 4) { out << " "; n++; }
//		out << std::setw(_OUTPUT_PRECISION_ + _OUTPUT_NUMBERSPACE_SIZE_ - n) << std::setprecision(_OUTPUT_PRECISION_) << std::left << matrix.get(i / matrix.columns(), i % matrix.columns()) << " ";
//	}
//	out << "]" << std::endl;
//
//	return out;
//}
//
////template<typename T>
////inline T& matrix_new<T>::operator[](size_t count){
////	return data[count];
////}
////
////template<typename T>
////inline T matrix_new<T>::operator[](size_t count) const{
////	return data[count];
////}
