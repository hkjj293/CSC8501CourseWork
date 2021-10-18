#include<iostream>
#include "CPM.h"
#include "BST.h"

int main() {
	CPM manager = CPM();
	manager.start();
	BST<int>* bst = new BST<int>();
	srand(10);
	for (int i = 0; i < 10; i++) {
		bst->add_node(rand() % 80 - 40);
	}
	bst->print();
	delete bst;
}
