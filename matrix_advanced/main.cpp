#include "matrix.h"

int main() {
	try {
		matrix<double> m_1(1024), m_2; m_1.set();
		int start = clock();
		//std::cout << m_1 << std::endl;
		//m_2 = m_1.inv();
		m_1 = m_1 * m_1;
		//std::cout << m_2;
		//unsigned int start = clock();

		std::cout << clock() - start;
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
	}

	return 0;
}