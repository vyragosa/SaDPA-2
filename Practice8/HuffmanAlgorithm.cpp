#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>

struct tNode {
	char ch;
	int freq;
	tNode *left;
	tNode *right;
};

tNode *getNode(char ch, int freq, tNode *left, tNode *right) {
	tNode *node = new tNode();
	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;
	return node;
}

struct compare {
	bool operator()(tNode *l, tNode *r) {
		return l->freq > r->freq;
	}
};


void encode(tNode *root, std::string str, std::unordered_map<char, std::string> &huffmanCode) {
	if (root == nullptr)
		return;
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = (str != "") ? str : "1";
	}
	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}


std::string buildHuffmanTree(std::string text) {
	std::unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}
	std::priority_queue<tNode *, std::vector<tNode *>, compare> pq;
	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}
	while (pq.size() != 1) {
		tNode *left = pq.top();
		pq.pop();
		tNode *right = pq.top();
		pq.pop();
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}
	tNode *root = pq.top();
	std::unordered_map<char, std::string> huffmanCode;
	encode(root, "", huffmanCode);
	std::string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}
	return str;
}

std::string readTextFile(std::string fileName) {
	std::ifstream file(fileName);
	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void writeBitsToFile(std::string bits, std::string fileName) {
	std::ofstream file(fileName, std::ios::binary);
	for(int i = 0; i < bits.size() - 8; i += 8) {
		char ch = 0;
		for (int j = 0; j < 8; j++) {
			ch = ch << 1;
			ch = ch | (bits[i + j] - '0');
		}
		file << ch;
	}
}

int main() {
	std::string text = readTextFile("input.txt");
	std::string bits = buildHuffmanTree(text);
	writeBitsToFile(bits, "output.txt");
	return 0;
}