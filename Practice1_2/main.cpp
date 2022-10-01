#include <iostream>
#define UINT_BIT (sizeof(uint32_t) * 8)
#define UINT_SHIFT (sizeof(uint32_t) + 1)
#define SIZE (8999999 / UINT_BIT + 1)


void sorting(uint32_t* arr);
void output(const uint32_t* arr);

int main() {
    uint32_t* arr = new uint32_t[SIZE]{ 0 };
    sorting(arr);
    output(arr);
    return 0;
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
        arr[num >> (sizeof(uint32_t) + 1)] |= 1 << (UINT_BIT - (num & (UINT_BIT - 1)) - 1);
    }
}

void output(const uint32_t* arr) {
    for (int i = 0; i < SIZE * UINT_BIT; i++)
        if (arr[i >> UINT_SHIFT] & 1 << (UINT_BIT- (i & (UINT_BIT - 1)) - 1))
            std::cout << i + 1000000 << '\n';
}
