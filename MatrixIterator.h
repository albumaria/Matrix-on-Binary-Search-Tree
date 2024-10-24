#include "Matrix.h"

class MatrixIterator
{

	friend class Matrix;

private:
	const Matrix& matrix;
	int i;
	int j;
	
	MatrixIterator(const Matrix& m);
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};

