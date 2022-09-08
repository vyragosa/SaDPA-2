#include <iostream>
#define UINT_BIT (sizeof(uint32_t) * 8)
#define SIZE (8999999 / UINT_BIT + 1)

void binaryOutput(uint32_t num, uint32_t pos);
void sorting(uint32_t* arr);
void output(uint32_t* arr);

int main() {
	uint32_t* arr = new uint32_t[SIZE]{ 0 };
	sorting(arr);
	output(arr);
	return 0;
}

void binaryOutput(uint32_t num, uint32_t pos) {
	uint32_t  mask = (1 << (UINT_BIT - 1));
	for (uint32_t i = 0; i < UINT_BIT; i++) {
		if ((num & mask) >> (UINT_BIT - 1 - i) == 1)
			std::cout << i + pos + 1000000 << '\t';
		mask = mask >> 1;
	}
}

void sorting(uint32_t* arr) {
	uint32_t num, arr_size;
	std::cout << "Enter size of array: ";
	std::cin >> arr_size;
	std::cout << "Enter array:\n";
	for (int i = 0; i < arr_size; i++) {
		std::cin >> num;
		if (num > 9999999 || num < 1000000) {
			std::cerr << "The number must contain only 7 digits!\n";
			exit(-1);
		}

		num -= 1000000;
		arr[num / UINT_BIT] |= 1 << (UINT_BIT - (num % UINT_BIT) - 1);
	}
}

void output(uint32_t* arr) {
	for (int i = 0; i < SIZE; i++)
		binaryOutput(arr[i], i * UINT_BIT);
}
