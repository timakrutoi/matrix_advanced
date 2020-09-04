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
		//int i = 0;
		//cin >> i;
		matrix<double> m_1(xz*8); m_1.set();
		matrix<double> m_2;
		unsigned int sum = 0;
		for (int i = 0; i < 1; i++) {
			clock_t beg = clock();
			m_2 = multi_strassen(m_1, m_1, 1);
			clock_t end = clock();
			sum += end - beg;
		}
		int_to_time(sum/1);
		/*sum = 0;
		for (int i = 0; i < 10; i++) {
			clock_t beg = clock();
			m_2 = m_1.inv();
			clock_t end = clock();
			sum += end - beg;
		}
		int_to_time(sum / 10);
		sum = 0;
		for (int i = 0; i < 10; i++) {
			clock_t beg = clock();
			double d = m_1.det();
			clock_t end = clock();
			sum += end - beg;
		}
		int_to_time(sum / 10);*/
	}
	catch (std::exception & e) {
		std::cerr << "Error: " << e.what();
	}

	return 0;
}