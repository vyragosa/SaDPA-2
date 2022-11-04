#include <iostream>
#include "include/RBTree.h"
using namespace std;

int main() {

    int data = 0;
    RBTree tree;
    Patient patient{ 1, "1", 1, "1", 1 };
    while (data != 10)
    {
        tree.insertValue(++data, patient);
    }
    tree.printTree(tree.root);
    tree.deleteValue(5);
    tree.printTree(tree.root);
    tree.deleteValue(10);
    tree.deleteValue(8);
    tree.printTree(tree.root);
    tree.deleteValue(2);
    tree.deleteValue(4);
	tree.printTree(tree.root);
    return 0;
}