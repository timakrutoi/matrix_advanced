#define xz 1024

#include "matrix.h"

int main() {
	try {
		matrix<double> m_1(xz), m_2(xz); m_1.set(1);
		int start = clock();

		m_2 = multi_strassen(m_1, m_1, 0);
		
		std::cout << clock() - start << std::endl;

		//start = clock();		
		//m_1 = m_1 * m_1;
		//std::cout << clock() - start;
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
	}

	return 0;
}