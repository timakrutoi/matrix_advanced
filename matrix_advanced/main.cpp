#include "matrix.h"
//#include "point.h"

int main() {
	try {
		matrix<double> m_1(4, 4); m_1.set();
		//m_1.set(0, 0, 7); m_1.set(0, 1, 4); m_1.set(1, 0, 8); m_1.set(1, 1, 2);
		std::cout << m_1 << std::endl;

		matrix<double> m = m_1.inv();
		std::cout << m_1.det() << std::endl;
		std::cout << m;
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
	}

	return 0;
}