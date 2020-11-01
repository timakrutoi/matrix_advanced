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

		matrix<double> m1(7); m1.set(1);

		string name1 = "C:\\Users\\Admin\\Desktop\\DB1.txt";
		string name2 = "C:\\Users\\Admin\\Desktop\\DB2.txt";

		//cout << m1;

		m1 = load(name1);
		//m1.save(name1);

		cout << m1;
		
		cout << "Done!";
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
	}

	return 0;
}