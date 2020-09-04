#define xz 1024
#include "matrix.h"

using namespace std;

void int_to_time(int time) {
	int milsec = time % 1000;
	time /= 1000;
	int sec = time % 60;
	time /= 60;
	int min = time % 60;
	time /= 60;
	std::cout << std::endl << "All time: " << time << ":" << min << ":" << sec << ":" << milsec << std::endl;
}

int main() {
	try {
		matrix<double> m_1(5, 5); m_1.set(1);
		matrix<double> m_2(m_1);
		matrix<double> m_3;
		//unsigned int sum = 0;

		//m_3 = m_1 * m_2;
		cout << m_2 << endl;

		//for (int i = 0; i < 1; i++) {
		//	clock_t beg = clock();
		//	m_2 = multi_strassen(m_1, m_1, 1);
		//	clock_t end = clock();
		//	sum += end - beg;
		//}

		//int_to_time(sum / 1);

	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
	}

	return 0;
}