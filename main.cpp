#include <iostream>
#include "matrix.h"

int main()
{
	Matrix<int, -1> matrix;
	matrix[0][0] = 100;
	std::cout << matrix[0][0] << std::endl;
	return 0;
}
