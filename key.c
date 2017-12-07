#include "key.h"

int matrix[4][4] = {{10,11,12,13},{14,15,16,17},{18,19,20,21},{22,23,24,25}};

int find_key_value (uint16_t row, uint16_t column)
{
	return matrix[row][column];
}