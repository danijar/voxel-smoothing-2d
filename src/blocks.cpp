#include "blocks.h"

#include <cstdlib>

using namespace std;
using namespace glm;

Blocks::Blocks(ivec2 max) : m_max(max)
{
	// Allocate memory for blocks
	m_data = new uint8_t[m_max.x * m_max.y];
	m_blocks = new uint8_t*[m_max.x];
	for (int i = 0; i < m_max.x; ++i)
		m_blocks[i] = m_data + m_max.y * i;

	// Initialize to zero
	memset(m_data, 0, m_max.x * m_max.y * sizeof uint8_t);
}

Blocks::~Blocks()
{
	// Free memory for blocks
	delete[] m_blocks;
	delete[] m_data;
}

void Blocks::set(glm::ivec2 block, uint8_t value)
{
	// Set block if in range
	if (in_range(block))
		m_blocks[block.x][block.y] = value;
}

uint8_t Blocks::get(ivec2 block, uint8_t fallback)
{
	// Return value if in range
	if (in_range(block))
		return m_blocks[block.x][block.y];
	return fallback;
}

bool Blocks::is(ivec2 block, bool fallback)
{
	// Return whether value if not zero if in range
	if (in_range(block))
		return (m_blocks[block.x][block.y] > 0);
	return fallback;
}

uint8_t **Blocks::get_pointer()
{
	return m_blocks;
}

bool Blocks::in_range(ivec2 block)
{
	// Check bounds
	bool inside_x = (0 <= block.x && block.x < static_cast<int>(m_max.x));
	bool inside_y = (0 <= block.y && block.y < static_cast<int>(m_max.y));
	return inside_x && inside_y;
}

ivec2 Blocks::get_size()
{
	return m_max;
}

void Blocks::fill_randomly()
{
	// loop over all blocks
	for (int i = 0; i < m_max.x; ++i)
	for (int j = 0; j < m_max.y; ++j)
		m_blocks[i][j] = rand() % 100 < 25;
}
