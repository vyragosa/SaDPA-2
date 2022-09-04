#include <iostream>
#define byteUInt (sizeof(uint32_t) * 8)
int firstOperation(uint32_t num) {
	return num | (1 << (byteUInt - 5) | 1 << (byteUInt - 7) | 1 << (byteUInt - 13));
}
int secondOperation(uint32_t num) {
	return num & ~ (1 << (byteUInt - 1) | 1 << (byteUInt - 2) | 1 << (byteUInt - 3) | 1 << (byteUInt - 4));
}
int thirdOperation(uint32_t num) {
	return num << 9;
}

int fourthOperation(uint32_t num) {
	return num >> 7;
}
int fifthOperation(uint32_t num, uint32_t bitToChange) {
	uint32_t mask = 1 << (byteUInt - 1);
	return num & ~(mask >> (bitToChange - 1));
}

int main() {
	uint32_t num = 0xfa, bitToChange;
	std::cout << "1. result: " << std::hex << std::uppercase << firstOperation(num) << std::endl;
	std::cout << "Enter number: ";
	std::cin >> num;
	std::cout << "Your number: " << num << std::endl;
	std::cout << "2. result: " << secondOperation(num) << std::endl;
	std::cout << "Enter number: ";
	std::cin >> num;
	std::cout << "3. result: " << std::dec << thirdOperation(num) << std::endl;
	std::cout << "Enter number: ";
	std::cin >> num;
	std::cout << "4. result: " << std::dec << fourthOperation(num) << std::endl;
	std::cout << "Enter number and bit u want to change: ";
	std::cin >> num >> bitToChange;
	std::cout << "Your number: " << std::hex << num << std::endl;
	std::cout << "5. result: " << fifthOperation(num, bitToChange) << std::endl;
	return 0;
}
