#include <iostream>
#include "matrix.h"

int main()
{
	const size_t max_size = 10;
	Matrix<int, 0> matrix;
	for (size_t i = 0; i < max_size; i++)
	{
		matrix[i][i] = i;
		matrix[i][(max_size - 1) - i] = (max_size - 1) - i;
	}

	for (size_t i = 1; i < max_size - 1; i++)
	{
	  for (size_t j = 1; j < max_size - 1; j++)
	  {
		std::cout << matrix[i][j] << " ";
	  }
	  std::cout << std::endl;
	}

	std::cout << matrix.size() << std::endl;

	for (const auto& cell : matrix)
	{
		for (const auto& position : cell.first)
		{
			std::cout << '[' << position << ']';
		}
		std::cout << '=' << cell.second << std::endl;
	}

	return 0;
}
