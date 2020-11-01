//#include "matrix.h"

template<typename T>
matrix<T>::matrix(uint32_t row, uint32_t column) {
	size_x = row; size_y = column;
	uint32_t temp_size = size_x * size_y;
	data = new T * [size_x];

	try {
		data[0] = new T[temp_size];
	}
	catch (const std::bad_alloc&) {
		delete[] data;
		throw;
	}

	std::fill_n(data[0], temp_size, T(0));
	for (uint32_t i = 1; i < size_x; i++) {
		data[i] = &data[0][i * size_y];
	}
}

template<typename T>
matrix<T>::matrix(uint32_t size_) {
	size_x = size_; size_y = size_;
	uint32_t temp_size = size_x * size_y;
	data = new T * [size_x];

	try {
		data[0] = new T[temp_size];
	}
	catch (const std::bad_alloc&) {
		delete[] data;
		throw;
	}

	std::fill_n(data[0], temp_size, T(0));
	for (uint32_t i = 1; i < size_x; i++) {
		data[i] = &data[0][i * size_y];
	}
}

template<typename T>
matrix<T>::matrix(const matrix& m) {
	size_x = m.size_x; size_y = m.size_y;
	uint32_t temp_size = size_x * size_y;
	data = new T * [size_x];

	try {
		data[0] = new T[temp_size];
	}
	catch (const std::bad_alloc&) {
		delete[] data;
		throw;
	}

	T* out = data[0]; T* r = m.data[0];

	for (uint32_t i = 0; i < temp_size; i++) {
		if (i % size_y == 0) data[i / size_y] = data[0] + i;

		out[i] = r[i];
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
void matrix<T>::set(uint32_t row, uint32_t column, T value) {
	if (row >= size_x || column >= size_y) throw std::out_of_range("Invalid args ( set )");

	data[row][column] = value;
}

template<typename T>
void matrix<T>::set(T val) {
	for (uint32_t i = 0; i < size_x; i++) {
		std::fill_n(data[i], size_y, val);
	}
}

template<typename T>
void matrix<T>::set() {
	srand(12342);

	uint32_t temp_size = size_x * size_y;
	T* out = data[0];

	for (uint32_t i = 0; i < temp_size; i++) {
		out[i] = T(rand() % 9) + 1;
	}
}

template<typename T>
const T matrix<T>::get(uint32_t row, uint32_t column) const {
	if (row >= size_x || column >= size_y) throw std::out_of_range("Invalid args ( get )");

	return data[row][column];
}

matrix<double> load(std::string name) {
	std::ifstream file;
	file.open(name);
	if (!file) throw std::logic_error("File not found ( load )");

	uint32_t size_x = 0, size_y = 0;
	std::string line;
	double smth;

	for (size_x = 0; std::getline(file, line); size_x++) {  // findin matrix size
		if (size_x == 0) {
			std::istringstream iss(line);
			for (size_y = 0; iss >> smth; size_y++);
		}
	}
	//file.seekg(file.beg);  // doesnt work
	file.close();
	file.open(name);

	matrix<double> temp(size_x, size_y);

	for (size_x = 0; std::getline(file, line); size_x++) {
		std::istringstream iss(line);
		for (size_y = 0; iss >> smth; size_y++) {
			temp.set(size_x, size_y, smth);
		}
	}

	file.close();
	return temp;
}

template<typename T>
void matrix<T>::save(std::string name) {
	std::ofstream file;
	file.open(name);

	for (uint32_t i = 0; i < this->rows(); i++) {
		for (uint32_t j = 0; j < this->columns(); j++) {
			file << this->get(i, j) << " ";
		}
		file << std::endl;
	}
}

template<typename T>
const uint32_t matrix<T>::rows() const {
	return size_x;
}

template<typename T>
const uint32_t matrix<T>::columns() const {
	return size_y;
}

template<typename T>
const void matrix<T>::resize(uint32_t x, uint32_t y) {
	/*if (x == 0) {
		uint32_t size = 1;
		while (size < size_x) {
			size <<= 1;
		}
		x = size; y = size;
	}*/

	matrix<T> temp(x, y);

	for (uint32_t i = 0; i < size_x; i++) {
		for (uint32_t j = 0; j < size_y; j++) {
			if (i < x && j < y) temp.data[i][j] = data[i][j];
		}
	}

	*this = temp;
}

template<typename T>
const matrix<T> matrix<T>::add_zero() const { //similar to resize method
	if (!size_x || !size_y) throw std::logic_error("Invalid size in add_zero");

	uint32_t size = 1;
	while (size < size_x) {
		size <<= 1;
	}

	matrix<T> temp(size, size);

	for (uint32_t i = 0; i < size; i++) {
		for (uint32_t j = 0; j < size; j++) {
			if (i < size_x && j < size_y) temp.data[i][j] = data[i][j];
		}
	}

	return temp;
}

template<typename T>
void matrix<T>::cut(matrix<T>& m1, matrix<T>& m2, matrix<T>& m3, matrix<T>& m4) {
	//uint32_t temp_size_x = size_x / 2, temp_size_y = size_y / 2;

	//if (m1.size_x != temp_size_x || m1.size_y != temp_size_y ||
	//	m2.size_x != temp_size_x || m2.size_y != temp_size_y ||
	//	m3.size_x != temp_size_x || m3.size_y != temp_size_y ||
	//	m4.size_x != temp_size_x || m4.size_y != temp_size_y) throw std::logic_error("Invalid sizes in cut");

	uint32_t temp_size = size_x / 2;

	for (uint32_t i = 0; i < size_y; i++) {
		for (uint32_t j = 0; j < size_x; j++) {
			if (i < temp_size && j < temp_size) m1.data[i][j] = data[i][j];
			if (i < temp_size && j >= temp_size) m2.data[i][j - temp_size] = data[i][j];
			if (i >= temp_size && j < temp_size) m3.data[i - temp_size][j] = data[i][j];
			if (i >= temp_size && j >= temp_size) m4.data[i - temp_size][j - temp_size] = data[i][j];
		}
	}
}

template<typename T>
matrix<T> matrix<T>::cut(uint32_t size) {
	matrix<T> temp(size);

	for (uint32_t i = 0; i < size; i++) {
		for (uint32_t j = 0; j < size; j++) {
			temp.data[i][j] = data[i][j];
		}
	}

	return temp;
}

template<typename T>
void matrix<T>::link(matrix<T>& m1, matrix<T>& m2, matrix<T>& m3, matrix<T>& m4) {
	//uint32_t temp_size_x = size_x / 2, temp_size_y = size_y / 2;

	//if (m1.size_x != temp_size_x || m1.size_y != temp_size_y ||
	//	m2.size_x != temp_size_x || m2.size_y != temp_size_y ||
	//	m3.size_x != temp_size_x || m3.size_y != temp_size_y ||
	//	m4.size_x != temp_size_x || m4.size_y != temp_size_y) throw std::logic_error("Invalid sizes in link");

	uint32_t temp_size = size_x / 2;

	for (uint32_t i = 0; i < size_y; i++) {
		for (uint32_t j = 0; j < size_x; j++) {
			if (i < temp_size && j < temp_size) data[i][j] = m1.data[i][j];
			if (i < temp_size && j >= temp_size) data[i][j] = m2.data[i][j - temp_size];
			if (i >= temp_size && j < temp_size) data[i][j] = m3.data[i - temp_size][j];
			if (i >= temp_size && j >= temp_size) data[i][j] = m4.data[i - temp_size][j - temp_size];
		}
	}
}

template<typename T>
matrix<T> matrix<T>::without_row_and_col(uint32_t row, uint32_t col) const {
	if (row >= size_x || col >= size_y) throw std::logic_error("Invalid sizes in without_row_and_col");
	matrix<T> temp(size_x - 1, size_y - 1);

	for (uint32_t i = 0, c = 0; i < temp.size_x; i++, c++) {
		for (uint32_t j = 0, v = 0; j < temp.size_y; j++, v++) {
			if (c == row) c++;
			if (v == col) v++;

			temp.data[i][j] = data[c][v];
		}
	}

	return temp;
}

template<typename T>
matrix<T> matrix<T>::LU_opt() const {
	if (!(size_x == size_y) || data[0][0] == 0) throw std::logic_error("Invalid matrix in LU_opt");

	matrix<T> L(size_x), U(size_x);

	T* udata = U.data[0];
	T* just_data = data[0];
	T needed_const = data[0][0];

	for (uint32_t i = 0; i < size_x; i++) {
		udata[i] = just_data[i];
		L.data[i][0] = data[i][0] / needed_const;

		//U.data[0][i] = data[0][i];
		//L.data[i][0] = (data[i][0] / data[0][0]);
	}

	for (uint32_t i = 1; i < size_x; i++) {
		T* udatai = U.data[i];
		T* just_datai = data[i];
		T udataii = U.data[i][i];

		for (uint32_t j = i; j < size_x; j++) {

			udatai[j] = just_datai[j];
			L.data[j][i] = data[j][i];  // not changed

			T udata2 = U.data[i][j];
			T ldata2 = L.data[j][i];

			T* ldatai = L.data[i];
			T* ldataj = L.data[j];

			for (uint32_t k = 0; k < i; k++) {
				udata2 = udata2 - (ldatai[k] * U.data[k][j]);
				ldata2 = ldata2 - (ldataj[k] * U.data[k][i]);

				//U.data[i][j] = U.data[i][j] - (L.data[i][k] * U.data[k][j]);
				//L.data[j][i] = L.data[j][i] - (L.data[j][k] * U.data[k][i]);
			}

			L.data[j][i] = L.data[j][i] / udataii;
		}
	}

	return U;
}

template<typename T>
matrix<T> matrix<T>::LU() const {
	if (!(size_x == size_y) || data[0][0] == 0) throw std::logic_error("Invalid matrix in LU");

	matrix<T> L(size_x), U(size_x);

	for (uint32_t i = 0; i < size_x; i++) {
		U.data[0][i] = data[0][i];
		L.data[i][0] = (data[i][0] / data[0][0]);
	}

	for (uint32_t i = 1; i < size_x; i++) {
		for (uint32_t j = i; j < size_x; j++) {

			U.data[i][j] = data[i][j];
			L.data[j][i] = data[j][i];

			for (uint32_t k = 0; k < i; k++) {
				U.data[i][j] = U.data[i][j] - (L.data[i][k] * U.data[k][j]);
				L.data[j][i] = L.data[j][i] - (L.data[j][k] * U.data[k][i]);
			}

			L.data[j][i] = L.data[j][i] / U.data[i][i];
		}
	}

	return U;
}

template<typename T>
const T matrix<T>::det() const {
	if (size_x != size_y) throw std::logic_error("Invalid matrix size in det");

	matrix<T> temp(*this); temp = temp.LU();
	T det = T(1);

	for (uint32_t i = 0; i < size_x; i++) {
		det = det * temp.data[i][i];
	}

	return det;
}

template<typename T>
const T matrix<T>::minor(uint32_t row, uint32_t col) const {
	matrix<T> temp = this->without_row_and_col(row, col);

	return temp.det();
}

template<typename T>
matrix<T> matrix<T>::inv() {//need optimization
	if (size_x != size_y) throw std::logic_error("Invalid matrix size in inverse matrix");

	matrix<T> E = matrix<T>::eye(size_x);
	matrix<T> copy(*this);

	for (uint32_t k = 0; k < size_x; k++) {
		if (copy.data[k][k] == 0) {
			uint32_t i = 0;

			for (i; i < size_x || copy.data[i][k] != 0; i++);

			for (uint32_t j = 0; j < size_x; j++) {
				T tmp = copy.data[k][j];
				copy.data[k][j] = copy.data[i][j];
				copy.data[i][j] = tmp;
				tmp = E.data[k][j];
				E.data[k][j] = E.data[i][j];
				E.data[i][j] = tmp;
			}
		}

		if (copy.data[k][k] != 1) {
			T coe = (T)1 / copy.data[k][k];

			for (uint32_t i = 0; i < size_x; i++) {
				copy.data[k][i] = copy.data[k][i] * coe;
				E.data[k][i] = E.data[k][i] * coe;
			}
		}

		for (uint32_t i = 0; i < size_x; i++) {
			if (i == k) continue;
			double coe = copy.data[i][k];

			for (uint32_t j = 0; j < size_x; j++) {
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
	uint32_t temp_size = size_x * size_y;
	T* l = data[0]; T* r = m.data[0]; T* out = temp.data[0];

	for (uint32_t i = 0; i < temp_size; i++) {
		out[i] = l[i] + r[i];
	}

	return temp;
}

template<typename T>
matrix<T> matrix<T>::operator-(const matrix& m) const {
	if (!(size_x == m.size_x && size_y == m.size_y)) throw std::logic_error("Matrices must be equal sizes to do '+'");

	matrix<T> temp(size_x, size_y);
	uint32_t temp_size = size_x * size_y;
	T* l = data[0]; T* r = m.data[0]; T* out = temp.data[0];

	for (uint32_t i = 0; i < temp_size; i++) {
		out[i] = l[i] - r[i];
	}

	return temp;
}

template<typename T>
matrix<T>& matrix<T>::operator=(matrix&& m) noexcept {
	if (this == &m) return *this;
	if (data) {
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
	if (data) {
		delete[] data[0];
		delete[] data;
		data = nullptr;
	}
	size_x = m.size_x; size_y = m.size_y;
	uint32_t temp_size = size_x * size_y;
	data = new T * [size_x];

	try {
		data[0] = new T[temp_size];
	}
	catch (const std::bad_alloc&) {
		delete[] data[0];
		throw;
	}

	T* out = data[0]; T* r = m.data[0];

	for (uint32_t i = 0; i < temp_size; i++) {
		if (i % size_y == 0) data[i / size_y] = data[0] + i;

		out[i] = r[i];
	}

	return *this;
}

template<typename T>
bool matrix<T>::operator==(const matrix<T>& m) const {
	if (size_x != m.size_x || size_y != m.size_y) return false;

	uint32_t temp_size = size_y * size_x;
	T* l = data[0]; T* r = m.data[0];

	for (uint32_t i = 0; i < temp_size; i++) {
		if (!(l[i] == r[i])) return false;
	}

	return true;
}

template<typename T>
bool matrix<T>::operator!=(const matrix<T>& m) const {
	return !(*this == m);
}

template<typename T>
matrix<T> matrix<T>::operator*(const matrix& m) const {
	if (size_y != m.size_x) throw std::logic_error("Invalid operator *");

	//if (size_x > 256) return multi_strassen(*this, m, 1);

	matrix<T> out(size_x, m.size_y);

	for (uint32_t i = 0; i < size_x; ++i) {
		T* c = out.data[i];

		for (uint32_t j = 0; j < m.size_y; ++j) {
			const T* a = data[i];

			for (uint32_t k = 0; k < size_y; ++k) {
				c[j] += a[k] * m.data[k][j];
			}
		}
	}

	return out;
}

template<typename T>
matrix<T> matrix<T>::operator*(const T& val) const {
	matrix<T> temp(*this);

	uint32_t temp_size = size_y * size_x;
	T* l = data[0];

	for (uint32_t i = 0; i < temp_size; i++) {
		l[i] = l[i] * val;
	}

	return temp;
}

template<typename T>
matrix<T> matrix<T>::multi_strassen(const matrix<T>& m1, const matrix<T>& m2, short mlt_thread) {

	matrix<T> temp1 = m1.add_zero(), temp2 = m2.add_zero();
	uint32_t out_size = m1.size_x;
	uint32_t size = temp1.size_x;

	if (size <= 256) {
		return m1.multi(m2);
	}

	matrix<T> out(size);
	size >>= 1;

	matrix<T> a1(size), a2(size), a3(size), a4(size);
	matrix<T> b1(size), b2(size), b3(size), b4(size);

	temp1.cut(a1, a2, a3, a4);
	temp2.cut(b1, b2, b3, b4);

	temp1.~matrix(); temp2.~matrix();

	matrix<T> p1, p2, p3, p4, p5, p6, p7;

	if (mlt_thread > 0) {
		mlt_thread--;

		std::future<matrix<T>> f1 = std::async(&matrix<T>::multi_strassen, a1, b2 - b4, mlt_thread);
		std::future<matrix<T>> f2 = std::async(&matrix<T>::multi_strassen, a1 + a2, b4, mlt_thread);
		std::future<matrix<T>> f3 = std::async(&matrix<T>::multi_strassen, a3 + a4, b1, mlt_thread);
		std::future<matrix<T>> f4 = std::async(&matrix<T>::multi_strassen, a4, b3 - b1, mlt_thread);
		std::future<matrix<T>> f5 = std::async(&matrix<T>::multi_strassen, a1 + a4, b1 + b4, mlt_thread);
		std::future<matrix<T>> f6 = std::async(&matrix<T>::multi_strassen, a2 - a4, b3 + b4, mlt_thread);
		std::future<matrix<T>> f7 = std::async(&matrix<T>::multi_strassen, a1 - a3, b1 + b2, mlt_thread);

		p1 = f1.get();
		p2 = f2.get();
		p3 = f3.get();
		p4 = f4.get();
		p5 = f5.get();
		p6 = f6.get();
		p7 = f7.get();

	}
	else {
		p1 = matrix<T>::multi_strassen(a1, b2 - b4, mlt_thread);
		p2 = matrix<T>::multi_strassen(a1 + a2, b4, mlt_thread);
		p3 = matrix<T>::multi_strassen(a3 + a4, b1, mlt_thread);
		p4 = matrix<T>::multi_strassen(a4, b3 - b1, mlt_thread);
		p5 = matrix<T>::multi_strassen(a1 + a4, b1 + b4, mlt_thread);
		p6 = matrix<T>::multi_strassen(a2 - a4, b3 + b4, mlt_thread);
		p7 = matrix<T>::multi_strassen(a1 - a3, b1 + b2, mlt_thread);
	}

	a1.~matrix(); a2.~matrix(); a3.~matrix(); a4.~matrix();
	b1.~matrix(); b2.~matrix(); b3.~matrix(); b4.~matrix();

	matrix<T> c1, c2, c3, c4;

	c1 = (p5 + p4) + (p6 - p2);
	c2 = (p1 + p2);
	c3 = (p3 + p4);
	c4 = (p1 - p3) + (p5 - p7);

	p1.~matrix(); p2.~matrix(); p3.~matrix(); p4.~matrix(); p5.~matrix(); p6.~matrix(); p7.~matrix();
	out.link(c1, c2, c3, c4);
	c1.~matrix(); c2.~matrix(); c3.~matrix(); c4.~matrix();
	out = out.cut(m1.size_x);

	return out;
}

template<typename T>
matrix<T> matrix<T>::eye(uint32_t size) {
	matrix<T> temp(size);

	for (uint32_t i = 0; i < size; i++) {
		temp.data[i][i] = T(1);
	}

	return temp;
}

template<typename T>
matrix<T> matrix<T>::t() {
	matrix<T> temp(size_y, size_x);

	for (uint32_t i = 0; i < size_y; i++) {
		for (uint32_t j = 0; j < size_x; j++) {
			temp.data[i][j] = data[j][i];
		}
	}

	return temp;
}

template<typename T>
matrix<T> matrix<T>::multi(const matrix<T>& m) const {
	if (size_y != m.size_x) throw std::logic_error("Use only sqaure matrices in 'multi' method");

	matrix<T> out(size_x);

	for (uint32_t i = 0; i < size_x; ++i) {
		T* c = out.data[i];

		for (uint32_t j = 0; j < m.size_y; ++j) {
			const T* b = m.data[j];
			T a = data[i][j];

			for (uint32_t k = 0; k < size_y; ++k) {
				c[j] += a * b[k];
			}
		}
	}

	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, matrix<T>& matrix) {
	out << "[ ";
	uint32_t size = matrix.columns() * matrix.rows();
	//std::cout.precision(_OUTPUT_PRECISION_);

	for (uint32_t i = 0; i < size; i++) {
		uint32_t n = 0;
		if (i % matrix.columns() == 0 && i > 0) out << "]\n[ ";
		if (!(matrix.get(i / matrix.columns(), i % matrix.columns()) < 0) && n <= 4) { out << " "; n++; }
		out << std::setw(_OUTPUT_PRECISION_ + _OUTPUT_NUMBERSPACE_SIZE_ - n) << std::setprecision(_OUTPUT_PRECISION_) << std::left << matrix.get(i / matrix.columns(), i % matrix.columns()) << " ";
		//out << matrix.get(i / matrix.columns(), i % matrix.columns()) << " ";
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
