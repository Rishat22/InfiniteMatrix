#include <iostream>
#include "Matrix.h"

int main()
{
	Matrix<int, -1> matrix;
	std::cout << matrix[0][0];
	return 0;
}
