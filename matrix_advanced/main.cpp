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
	std::cout << "All time: " << time << ":" << min << ":" << sec << ":" << milsec << std::endl;
}

int main() {
	try {
		std::cout << "Starting..." << std::endl;

		matrix<double> m(5);

		m = matrix<double>::load("C:\\Users\\Admin\\Desktop\\DB\\lab20\\DB5.txt");
		cout << m;

		cout << "Done!";
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
	}

	return 0;
}