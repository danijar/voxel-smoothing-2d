#pragma once

#include <vector>
#include <stdint.h>

class Blocks
{
public:
	Blocks(int X, int Y);
	~Blocks();
	void Set(int X, int Y, uint8_t Value = 1);
	uint8_t Get(int X, int Y, uint8_t Fallback = 1);
	bool Is(int X, int Y, bool Fallback = true);
	uint8_t **Pointer();
	int X();
	int Y();
	void Random();
private:
	const size_t x, y;
	uint8_t *data;
	uint8_t **blocks;
};
