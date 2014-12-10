#include "blocks.h"

#include <cstdlib>
using namespace std;

Blocks::Blocks(int X, int Y) : x(X), y(Y)
{
	// allocate memory for blocks
	data = new uint8_t[x * y];
	blocks = new uint8_t*[x];
	for (size_t i = 0; i < x; ++i)
		blocks[i] = data + y * i;

	// initialize to zero
	memset(data, 0, x * y * sizeof uint8_t);
}

Blocks::~Blocks()
{
	// free memory for blocks
	delete[] blocks;
	delete[] data;
}

void Blocks::Set(int X, int Y, uint8_t Value)
{
	// check bounds
	bool inside = (0 <= X && X < (int)x) && (0 <= Y && Y < (int)y);
	if (!inside)
		return;

	// set block
	blocks[X][Y] = Value;
}

uint8_t Blocks::Get(int X, int Y, uint8_t Fallback)
{
	// check bounds
	bool inside = (0 <= X && X < (int)x) && (0 <= Y && Y < (int)y);

	// return value or fallback
	if (inside)
		return blocks[X][Y];
	else
		return Fallback;
}

bool Blocks::Is(int X, int Y, bool Fallback)
{
	// check bounds
	bool inside = (0 <= X && X < (int)x) && (0 <= Y && Y < (int)y);

	// return value or fallback
	if (inside)
		return blocks[X][Y] != 0;
	else
		return Fallback;
}

uint8_t **Blocks::Pointer()
{
	return blocks;
}

int Blocks::X()
{
	return x;
}

int Blocks::Y()
{
	return y;
}

void Blocks::Random()
{
	// loop over all blocks
	for (size_t i = 0; i < x; ++i)
	for (size_t j = 0; j < y; ++j)
		blocks[i][j] = rand() % 100 < 25;
}
