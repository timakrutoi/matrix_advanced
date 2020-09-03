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
		matrix<double> m_1(xz*4); m_1.set();
		matrix<double> m_2;
		int i;
		int sum = 0;
		for (i = 0; i < 10; i++) {
			clock_t beg = clock();
			m_2 = multi_strassen(m_1, m_1, 1);
			//m_2 = m_1.multi(m_1);
			clock_t end = clock();
			sum += end - beg;
		}
		sum /= i;
		int_to_time(sum);
		//cout << m_2;
			//system("PAUSE");
		//}
		/*beg = clock();
		m_2 = m_1.multi(m_1);
		end = clock();
		int_to_time(end - beg);*/

	/*	beg = clock();
		m_2 = m_1 * m_1;
		end = clock();
		int_to_time(end - beg);*/
		
		
		//for (int i = 0; i < 10; i++) {
			
			
		//}
		
		//std::cout << m_2;
		//system ("PAUSE");
		//m_1.~matrix();
		//system("PAUSE");
		//std::cout << "lol";
		//system("PAUSE");
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what();
	}

	return 0;
}