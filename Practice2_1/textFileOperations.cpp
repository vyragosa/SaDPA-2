#include "textFileOperations.h"

int readTextFile(std::string nameTf) {
	int x;
	std::ifstream tf(nameTf);
	if (!tf.good())
		return -1;
	while (tf >> x) {
		std::cout << x << '\n';
	}
	tf.close();
	return 0;
}

int createTextFile(std::string nametf, int size) {
	std::ofstream tf(nametf);
	if (!tf.good())
		return -1;

	for (int i = 0; i < size; i++) {
		int x = rand() % 100;
		//std::cin >> x;
		if (x % 4 == 0)
			tf << '\n';
		tf << x << ' ';
	}
	tf.close();
	return 0;
}

int addTextToFile(std::string nameTf, int a) {
	std::ofstream tf(nameTf, std::ios::app);
	if (!tf.good())
		return -1;
	tf << '\n' << a;
	tf.close();
	return 0;
}

int countNInFile(std::string nameTf) {
	int x, cnt = 0;
	std::ifstream tf(nameTf);
	if (!tf.good())
		return -1;
	while (tf >> x)
		cnt++;
	tf.close();
	return cnt;
}

int findNByNumber(std::string nameTf, int num) {
	int x, cnt = 0;
	std::ifstream tf(nameTf);
	if (!tf.good())
		return -1;
	while (tf >> x) {
		if (x == num) {
			tf.close();
			return cnt;
		}
		cnt++;
	}
	tf.close();
	return -1;
}

int createTextFilePrime(std::string nameItf, std::string nameOtf) {
	std::ifstream itf(nameItf);
	std::ofstream otf(nameOtf);
	if (!itf.good() || !otf.good())
		return -1;
	int x;
	while (itf >> x)
		if (isPrime(x))
			otf << x << "\n";
	itf.close();
	otf.close();
	return 0;
}

bool isPrime(int num) {
	for (int i = 2; i <= num / 2; i++)
		if (num % i == 0)
			return false;
	return true;
}