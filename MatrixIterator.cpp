#include "MatrixIterator.h"
#include "Matrix.h"
#include <exception>

using namespace std;

MatrixIterator::MatrixIterator(const Matrix& m) : matrix(m) {

	this->i = 0;
	this->j = 0;
}
// BC = WC = TC = Theta(1)


void MatrixIterator::first()
{
	this->i = 0;
	this->j = 0;
}
// BC = WC = TC = Theta(1)


void MatrixIterator::next()
{
	if (!this->valid()) {
		throw exception();
	}

	if (this->j < this->matrix.nrColumns() - 1) {
		this->j++;
	}
	else if (this->j == this->matrix.nrColumns() - 1) {
		this->i++;
		this->j = 0;
	}

	return;
}
// BC = WC = TC = Theta(1)


TElem MatrixIterator::getCurrent() const
{
	if (!this->valid()) { //even if it is checked by function element
		throw exception();
	}
	return this->matrix.element(this->i, this->j);
}
// BC = Theta(1) if the element searched is the root, or the tree is empty
// WC = WC of element = Theta(n) - if the node searched is at the depth of the tree
// TC = O(n)


bool MatrixIterator::valid() const
{
	if (this->i < 0 or this->j < 0 or this->i >= this->matrix.nrLines() or j >= this->matrix.nrColumns())
		return false;

	return true;
}
// BC = WC = TC = Theta(1)