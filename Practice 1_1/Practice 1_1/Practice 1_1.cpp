#include <iostream>
#define UINT_BIT (sizeof(uint32_t) * 8)

void binaryOutput(uint32_t x);
uint32_t firstOperation(uint32_t num);
uint32_t secondOperation(uint32_t num);
uint32_t thirdOperation(uint32_t num);
uint32_t fourthOperation(uint32_t num);
uint32_t fifthOperation(uint32_t num, uint32_t bitToChange);

int main() {
	uint32_t num = 0xe0fa4c7f, bitToChange;
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
	if (bitToChange > 32 || bitToChange < 0) {
		std::cerr << "Input Error!\n";
		return -1;
	}
	std::cout << "Your number: " << std::hex << num << std::endl;
	binaryOutput(fifthOperation(num, bitToChange));
	return 0;
}

uint32_t firstOperation(uint32_t num) {
	uint32_t mask = 1 << (UINT_BIT - 5) | 1 << (UINT_BIT - 7) | 1 << (UINT_BIT - 13);
	//uint32_t mask = 0xA080000;
	return num | mask;
}

uint32_t secondOperation(uint32_t num) {
	uint32_t mask = ~(1 << (UINT_BIT - 1) | 1 << (UINT_BIT - 2) | 1 << (UINT_BIT - 3) | 1 << (UINT_BIT - 4));
	//uint32_t mask = 0xFFFFFFF;
	return num & mask;
}

uint32_t thirdOperation(uint32_t num) {
	return num << 9;
}

uint32_t fourthOperation(uint32_t num) {
	return num >> 7;
}

uint32_t fifthOperation(uint32_t num, uint32_t bitToChange) {
	uint32_t mask = 1 << (UINT_BIT - 1);
	//uint32_t mask = 0x80000000;
	return num & ~(mask >> (bitToChange - 1));
}

void binaryOutput(uint32_t x) {
	std::cout << "Result: ";
	uint32_t  mask = (1 << (UINT_BIT - 1));
	for (int i = 0; i < UINT_BIT; i++) {
		std::cout << ((x & mask) >> (UINT_BIT - 1 - i));
		mask = mask >> 1;
	}
	std::cout << std::endl;
}
