#include <iostream>
#define UINT_BIT (sizeof(uint32_t) * 8)

void binaryOutput(uint32_t x);
int firstOperation(uint32_t num);
int secondOperation(uint32_t num);
int secondOperation(uint32_t num);
int fourthOperation(uint32_t num);
int fifthOperation(uint32_t num, uint32_t bitToChange);

int main() {
	uint32_t num = 0xfa, bitToChange;
	binaryOutput(firstOperation(num));
	std::cout << "Enter number: ";
	std::cin >> num;
	std::cout << "Your number: " << num << std::endl;
	binaryOutput(secondOperation(num));
	std::cout << "Enter number: ";
	std::cin >> num;
	binaryOutput(thirdOperation(num));
	std::cout << "Enter number: ";
	std::cin >> num;
	binaryOutput(fourthOperation(num));
	std::cout << "Enter number and bit u want to change: ";
	std::cin >> num >> bitToChange;
	std::cout << "Your number: " << std::hex << num << std::endl;
	binaryOutput(fifthOperation(num, bitToChange));
	return 0;
}

void binaryOutput(uint32_t x) {
	std::cout << "Result: ";
	for (int i = 1; i <= UINT_BIT; i++)
		std::cout << (x >> (UINT_BIT - i));
	std::cout << std::endl;
}

int firstOperation(uint32_t num) {
	return num | (1 << (UINT_BIT - 5) | 1 << (UINT_BIT - 7) | 1 << (UINT_BIT - 13));
}

int secondOperation(uint32_t num) {
	return num & ~(1 << (UINT_BIT - 1) | 1 << (UINT_BIT - 2) | 1 << (UINT_BIT - 3) | 1 << (UINT_BIT - 4));
}

int thirdOperation(uint32_t num) {
	return num << 9;
}

int fourthOperation(uint32_t num) {
	return num >> 7;
}

int fifthOperation(uint32_t num, uint32_t bitToChange) {
	uint32_t mask = 1 << (UINT_BIT - 1);
	return num & ~(mask >> (bitToChange - 1));
}
