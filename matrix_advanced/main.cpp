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
		std::cout << "Starting..." << std::endl;

		matrix<double> m1(xz); m1.set(1);
		matrix<double> m2(xz); m2.set(1);
		matrix<double> m3(xz); m3.set(xz);
		//cout << m1 << endl;
		//cout << m2 << endl;
		int i;
		int sum = 0;
		double temp = 0;
		//for (int i = 0; i < 100; i++) {
			clock_t beg = clock();
			m2 = m2.multi(m1);
			//m2 = matrix<double>::multi_strassen(m1, m1, 1);
			clock_t end = clock();
			sum += end - beg;
		//}
		int_to_time(sum / 1);
		cout << endl << (m2 == m3) << endl;

	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
	}

	return 0;
}