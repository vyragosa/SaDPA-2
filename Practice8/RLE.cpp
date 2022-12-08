#include <iostream>
#include <string>

std::string RLE(const std::string &str) {
	std::string result;
	int count = 1;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == str[i + 1]) {
			count++;
		} else {
			result += str[i];
			if (count > 1) {
				result += std::to_string(count);
			}
			count = 1;
		}
	}
	return result;
}

int main() {
	std::string str;
	std::cin >> str;
//	WWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW
//	ABCABCABCDDDFFFFFF
	std::cout << RLE(str);
	return 0;
}