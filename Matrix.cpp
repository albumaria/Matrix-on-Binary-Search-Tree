#include "Matrix.h"
#include "MatrixIterator.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->columns = nrCols;
	this->lines = nrLines;
	this->root = nullptr;
}
// BC = WC = TC = Theta(1)


int Matrix::nrLines() const {
	
	return this->lines;
}
// BC = WC = TC = Theta(1)


int Matrix::nrColumns() const {
	
	return this->columns;
}
// BC = WC = TC = Theta(1)


TElem Matrix::element(int i, int j) const { //acts like a search
	
	if (i >= this->lines || j >= this->columns || i < 0 || j < 0)
		throw exception();

	BSTNode* currentNode = this->root;

	while (currentNode != nullptr) {
		if (currentNode->info.line == i and currentNode->info.column == j)
			return currentNode->info.value;

		else if (i < currentNode->info.line || (i == currentNode->info.line && j < currentNode->info.column)) { //go to left 
			currentNode = currentNode->left;
		}
		else { // go to right
			currentNode = currentNode->right;
		}

	}

	return NULL_TELEM;
}
// BC = Theta(1) - if the node is the root or if the indexes are invalid or there are no nodes
// WC = Theta(n) - if the node we search for is at the lowest depth of the tree
// TC = O(n)


TElem Matrix::modify(int i, int j, TElem e) {
	
	if (i >= this->lines || j >= this->columns || i < 0 || j < 0)
		throw exception();

	if (e == NULL_TELEM) { // delete node if it exists, nothing otherwise
		BSTNode* currentNode = this->root;
		bool found = false;

		while (currentNode != nullptr and !found) {
			if (currentNode->info.line == i and currentNode->info.column == j)
				found = true;

			else if (i < currentNode->info.line || (i == currentNode->info.line && j < currentNode->info.column)) { //go to left
				currentNode = currentNode->left;
			}
			else { // go to right
				currentNode = currentNode->right;
			}
		}

		if (found == true) { // delete
			TElem value = currentNode->info.value;
			deleteNode(currentNode);
			return value;
		}
		else // the node was not found and it's value is 0
			return NULL_TELEM;
	}
	else { // insert if it doesn't exist, modify otherwise
		BSTNode* currentNode = this->root;
		bool found = false;

		while (currentNode != nullptr and !found) {
			if (currentNode->info.line == i and currentNode->info.column == j)
				found = true;

			else if (i < currentNode->info.line || (i == currentNode->info.line && j < currentNode->info.column)) { //go to left
				currentNode = currentNode->left;
			}
			else { // go to right
				currentNode = currentNode->right;
			}
		}

		if (found == true) { // modify
			TElem value = currentNode->info.value;
			currentNode->info.value = e;
			return value;
		}
		else { // insert
			TCell newTriple;
			newTriple.column = j;
			newTriple.line = i;
			newTriple.value = e;
			this->root = insertNode(this->root, newTriple);
			return NULL_TELEM;
		}
			

	}
}
// BC = Theta(1) - if the element is found at the root and we modify it with a new value 
// (as in, when inserting for the first time the root, when deleting a tree with just a root)
// WC = Theta(n) - if we have to traverse to the lowest depth of the tree to find the element to modify, insert, or delete
// TC = O(n)



BSTNode* Matrix::parent(BSTNode* node) {
	BSTNode* currentNode = this->root;

	if (node == nullptr || this->root == nullptr || this->root == node)
		return nullptr;
	
	while (currentNode != nullptr && currentNode->left != node && currentNode->right != node) {
		if (node->info.line < currentNode->info.line || (node->info.line == currentNode->info.line && node->info.column < currentNode->info.column)) { //go to left
			currentNode = currentNode->left;
		}
		else { // go to right
			currentNode = currentNode->right;
		}
	}
	return currentNode;
}
// BC = Theta(1) - if the node is the root or if the node doesn't exist (nullptr)
// WC = Theta(n) - if the minimum node is at the lowest depth of the tree, it searches the whole depth
// TC = O(n)


void Matrix::deleteNode(BSTNode* currentNode) {
	if (currentNode->left == nullptr and currentNode->right == nullptr) { //no descendants

		BSTNode* previousNode = parent(currentNode);

		if (previousNode == nullptr) { // the searched node is the root
			this->root = nullptr;
			delete[] currentNode;
			return;
		}
		else {
			if (previousNode->left == currentNode) {
				previousNode->left = nullptr;
				delete[] currentNode;
				return;
			}
			else {
				previousNode->right = nullptr;
				delete[] currentNode;
				return;
			}
		}
	}
	else if (currentNode->left == nullptr and currentNode->right != nullptr) { //if it has one descendant on the right

		BSTNode* previousNode = parent(currentNode);

		if (previousNode == nullptr) {
			this->root = currentNode->right;
			delete[] currentNode;
			return;
		}
			
		else if (previousNode->left == currentNode) {
			previousNode->left = currentNode->right;
			delete[] currentNode;
			return;
		}
			
		else {
			previousNode->right = currentNode->right;
			delete[] currentNode;
			return;
		}
			
	}
	else if (currentNode->left != nullptr and currentNode->right == nullptr) { // if it has one descendant on the left

		BSTNode* previousNode = parent(currentNode);

		if (previousNode == nullptr) {
			this->root = currentNode->left;
			delete[] currentNode;
			return;
		}

		else if (previousNode->left == currentNode) {
			previousNode->left = currentNode->left;
			delete[] currentNode;
			return;
		}
			
		else {
			previousNode->right = currentNode->left;
			delete[] currentNode;
			return;
		}
			
	}
	else { // if it has 2 descendants
		//find the minimum from the right subtree, move it to the node to be deleted, delete the minimum node
		BSTNode* minimumNode = minimumFromNode(currentNode->right);
		currentNode->info = minimumNode->info;

		deleteNode(minimumNode);
	}
}
// BC = Theta(1) - if the node is a leaf or the root with no children and parent is a Theta(1) operation
// WC = Theta(n) - if the node to be deleted has two children and we have to find the minimum node from the 
// right subtree, which can be at the lowest depth of the tree
// TC = O(n)


BSTNode* Matrix::minimumFromNode(BSTNode* node) {
	if (node == nullptr)
		return nullptr;
	else {
		while (node->left != nullptr)
			node = node->left;

		return node;
	}
}
// BC = Theta(1) - if the node is the root
// WC = Theta(n) - if the minimum node is at the lowest depth of the tree
// TC = O(n)


BSTNode* Matrix::insertNode(BSTNode* node, TCell e) {

	BSTNode* newNode = new BSTNode();
	newNode->info = e;
	newNode->right = nullptr;
	newNode->left = nullptr;

	if (node == nullptr) {
		return newNode;
	}

	BSTNode* parent = nullptr;
	BSTNode* current = node;
	while (current != nullptr) {
		parent = current;
		if (e.line < current->info.line || (e.line == current->info.line && e.column < current->info.column)) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	if (parent == nullptr) {
		return newNode;
	}

	if (e.line < parent->info.line || (e.line == parent->info.line && e.column < parent->info.column)) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}

	return node;
}
// BC = Theta(1) - if the node is the root
// WC = Theta(n) - if the position to be inserted is at the lowest depth of the tree
// TC = O(n)


MatrixIterator Matrix::iterator() const {
	return MatrixIterator(*this);
}
// BC = WC = TC = Theta(1)
