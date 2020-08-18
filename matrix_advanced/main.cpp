#include "matrix.h"

int main() {
	try {
		matrix<double> m_1(10), m_2; m_1.set();
		std::cout << m_1 << std::endl;
		m_2 = m_1.inv();
		std::cout << m_2;
		//unsigned int start = clock();

		//matrix<double> m = multi_strassen(m_1, m_1, 0);
		//std::cout << m;
		//for (int i = 1; i < 100; i++) {
		//	matrix<double> m_1(i); m_1.set();
		//	//std::cout << pow(i, 3) << std::endl;
		//	//m_1.old_det();

		//	unsigned int start = clock();

		//	//<double> m = m_1.inv();

		//	//std::cout << clock() - start << std::endl;
		//}

		//matrix<double> m = m_1.LU();

		//std::cout << m_1.det() << std::endl;
		//std::cout << clock() - start;
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
	}

	return 0;
}