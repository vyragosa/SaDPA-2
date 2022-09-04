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
void binaryOutput(uint32_t x) {
	std::cout << "Result: ";
	uint32_t  mask = (1 << (byteUInt - 1));
	for (int i = 1; i <= byteUInt; i++)
	{
		std::cout << ((x & mask) >> (byteUInt - i));
		mask = mask >> 1;
	}
	std::cout << std::endl;
}

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
