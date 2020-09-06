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

		matrix<double> m1(xz * 2); m1.set(1);
		unsigned int sum = clock();

		m1 = matrix<double>::multi_strassen(m1, m1, 1);
		//m1 = matrix<double>::eye(4);
		//cout << m1 << endl;

		int_to_time(clock() - sum);

	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
	}

	return 0;
}