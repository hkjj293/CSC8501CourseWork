#pragma once
#include <string>
#include <iostream>

template <typename T>
struct nodeTemplate {
	T value;
	struct nodeTemplate* left;
	struct nodeTemplate* right;
};

template <typename T>
class BST {
public:
	BST();
	~BST();
	void add_node(T val);
	inline void get_leftmost(struct nodeTemplate<T>*& curr, struct nodeTemplate<T>**& stack, int& depth);
	void print();
	bool has_element(T val);
private:
	struct nodeTemplate<T>* root;
	int depth;
};

template <typename T>
BST<T>::BST() {
	root = NULL;
	depth = 0;
}

template <typename T>
BST<T>::~BST() {
	struct nodeTemplate<T>* curr = this->root;
	struct nodeTemplate<T>** stack = new nodeTemplate<T> * [this->depth];
	for (int i = 0; i < this->depth; i++) {
		stack[i] = NULL;
	}
	int depth = 1;
	while (curr != NULL || depth != 1) {
		this->get_leftmost(curr, stack, depth);
		struct nodeTemplate<T>* disposal = curr;
		curr = curr->right;
		std::cout << "deleting " << disposal->value << std::endl;
		delete disposal;
		disposal = NULL;
		std::cout << "deleted" << std::endl;
	}
	delete[] stack;
	stack = NULL;
	root = NULL;
}

template <typename T>
void BST<T>::add_node(T val) {
	struct nodeTemplate<T>** curr = &(this->root);
	int depth = 1;
	while ((*curr) != NULL) {
		depth++;
		if (val < (*curr)->value) {
			curr = &((*curr)->left);
		}
		else {
			curr = &((*curr)->right);
		}
	}
	*curr = new nodeTemplate<T>;
	(*curr)->left = NULL;
	(*curr)->right = NULL;
	(*curr)->value = val;
	this->depth += (this->depth < depth) * (depth - this->depth);
}

template <typename T>
void BST<T>::print() {
	struct nodeTemplate<T>* curr = this->root;
	struct nodeTemplate<T>** stack = new nodeTemplate<T> * [this->depth];
	for (int i = 0; i < this->depth; i++) {
		stack[i] = NULL;
	}
	int depth = 1;
	while (curr != NULL || depth != 1) {
		this->get_leftmost(curr, stack, depth);
		std::cout << curr->value << std::endl;
		curr = curr->right;
	}
	delete[] stack;
	stack = NULL;
}

template <typename T>
bool BST<T>::has_element(T val) {
	struct nodeTemplate<T>* curr = this->root;
	while (curr != NULL) {
		if (val == curr->value) return true;
		if (val < curr->value) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}
	return false;
}

template <typename T>
inline void BST<T>::get_leftmost(struct nodeTemplate<T>*& curr, struct nodeTemplate<T>**& stack, int& depth) {
	while (curr != NULL) {
		stack[depth - 1] = curr;
		depth++;
		curr = (curr)->left;
	}
	depth--;
	curr = stack[depth - 1];
}
