#include <iostream>
#include <fstream>

int readTextFile(std::string nameTf);
int createTextFile(std::string nameItf, std::string nameOtf);
int addTextToFile(std::string nameTf, int a);
int countNInFile(std::string nameTf);
int foundNByNumber(std::string nameTf, int num);
bool isPrime(int num);

int main() {
	std::string fileName, newFileName;
	std::cout << "Enter name of your text file: ";
	std::cin >> fileName;
	int code = readTextFile(fileName);

	if (code == -1) {
		std::cout << "File not found";
		return code;
	}

	std::cout << "Enter name of new text file: ";
	std::cin >> newFileName;

	code = createTextFile(fileName, newFileName);
	if (code == -1) {
		std::cout << "File not created";
		return code;
	}
	std::cout << foundNByNumber(fileName, 123);
	std::cout << "Retult:\n";
	readTextFile(newFileName);
	return 0;
}

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

int createTextFile(std::string nameItf, std::string nameOtf) {
	std::ifstream itf(nameItf);
	if (!itf.good())
		return -1;
	std::ofstream otf(nameOtf);
	int x;
	while (itf >> x) {
		if (isPrime(x))
			otf << x << ' ';
	}
	itf.close();
	otf.close();
	return 0;
}

int addTextToFile(std::string nameTf, int a) {
	std::ofstream tf(nameTf, std::ios::app);
	if (!tf.good())
		return -1;
	tf << ' ' << a;
	tf.close();
	return 0;
}

int countNInFile(std::string nameTf) {
	int x, cnt = 0;
	std::ifstream tf(nameTf);
	if (!tf.good())
		return -1;
	while (tf >> x) {
		cnt++;
	}
	tf.close();
	return cnt;
}

int foundNByNumber(std::string nameTf, int num) {
	int x, cnt = 0;
	std::ifstream tf(nameTf);
	if (!tf.good())
		return -1;
	while (tf >> x) {
		if (x == num)
			return cnt;
		cnt++;
	}
	tf.close();
	return -1;
}

bool isPrime(int num) {
	for (int i = 2; i <= num / 2; i++)
		if (num % i == 0)
			return false;
	return true;
}