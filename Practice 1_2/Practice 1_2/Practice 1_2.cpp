#include <iostream>
#define byteUInt (sizeof(uint32_t) * 8)
#define size (9000000 / byteUInt + 1)

void binaryOutput(uint32_t num, uint32_t pos) {
	uint32_t  mask = 1 << (byteUInt - 1);
	for (uint32_t i = 1; i <= byteUInt; i++) {
		if ((num & mask) >> (byteUInt - i) == 1)
			std::cout << i + pos - 1 + 1000000 << '\t';
		mask >>= 1;
	}
}

void sorting(uint32_t* arr, uint32_t arr_size) {
	int num;
	for (int i = 0; i < arr_size; i++) {
		std::cin >> num;
		num -= 1000000;
		arr[num / byteUInt] |= 1 << (byteUInt - (num % byteUInt) - 1);
	}
}

void output(uint32_t* arr, uint32_t arr_size) {
	uint32_t num;
	for (int i = 0; i < size; i++) {
		binaryOutput(arr[i], i * byteUInt);
	}
}

int main() {
	uint32_t arr_size;
	std::cin >> arr_size;
	uint32_t* arr = new uint32_t[size]{ 0 };
	sorting(arr, arr_size);
	output(arr, arr_size);
	return 0;
}