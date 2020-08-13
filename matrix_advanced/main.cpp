#include "matrix.h"
#include "ctime"

int main() {
	try {
		matrix<double> m_1(256); m_1.set();
		unsigned int start = clock();
		
		std::cout << m_1.det() << std::endl;
		std::cout << clock() - start;
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
	}

	return 0;
}