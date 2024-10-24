#pragma once

typedef int TElem;
#define NULL_TELEM 0

typedef struct TCell
{
	int line = -1;
	int column = -1;
	TElem value = 0;

	//TCell(int l = -1, int c = -1, TElem v = 0) : line(l), column(c), value(v) {}

}TCell;

typedef struct BSTNode
{
	TCell info;
	BSTNode* left = nullptr;
	BSTNode* right = nullptr;

	//BSTNode(TCell cell) : info(cell), left(nullptr), right(nullptr) {}

}BSTNode;

class MatrixIterator;
class Matrix {
private:
	BSTNode* root;
	int lines;
	int columns;

	BSTNode* parent(BSTNode* node);
	void deleteNode(BSTNode* currentNode);
	BSTNode* minimumFromNode(BSTNode* start);
	BSTNode* insertNode(BSTNode* node, TCell e);

public:

	Matrix(int nrLines, int nrCols);

	int nrLines() const;

	int nrColumns() const;

	TElem element(int i, int j) const;

	TElem modify(int i, int j, TElem e);

	MatrixIterator iterator() const;

};
