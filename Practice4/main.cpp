#include <iostream>
#include "perfectBalancedTree.h"

int main() {
	int menu = 1, num;
	perfectBalancedTree* tree;
	while (menu) {
		std::cout << "Press 1 create perfect balanced tree\n"
			<< "Press 2 print tree from root\n"
			<< "Press 3 to get average\n"
			<< "Press 4 to delete tree\n"
			<< "Press 0 to exit program\n";
		std::cin >> menu;
		switch (menu) {
		case 1:
			std::cout << "Enter size of tree: ";
			std::cin >> num;
			tree = new perfectBalancedTree(num);
			break;
		case 2:
			tree->printTree(tree->root);
			break;
		case 3:
			tree->getAverage(tree->root);
			break;
		case 4:
			delete tree;
			break;
		default:
			return 0;
		}
	}
}
